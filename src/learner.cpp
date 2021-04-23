#include "learner.h"

#include <algorithm>
#include <utility>

CoordinateDescent::CoordinateDescent(
    std::function<double(const std::vector<double>&)> error_fcn,
    std::vector<double> initial_parameters,
    std::vector<double> parameter_change, double tolerance, double up_factor,
    double down_factor)
    : error_fcn{std::move(error_fcn)},
      initial_parameters_{std::move(initial_parameters)},
      parameter_change_{std::move(parameter_change)},
      up_factor_{up_factor},
      down_factor_{down_factor},
      tolerance_{tolerance},
      mean_squared_error_{0} {
  assert(initial_parameters_.size() == parameter_change_.size());
}

const std::vector<double>& CoordinateDescent::BestParameters() const {
  return best_parameters_;
}

double CoordinateDescent::MeanSquaredError() const {
  return mean_squared_error_;
}

void CoordinateDescent::Learn() {
  best_parameters_ = initial_parameters_;
  mean_squared_error_ = error_fcn(best_parameters_);
  auto parameter_change = parameter_change_;
  double mse;
  while (Norm(parameter_change) > tolerance_) {
    for (int i = 0; i < best_parameters_.size(); ++i) {
      best_parameters_[i] += parameter_change[i];
      mse = error_fcn(best_parameters_);
      if (mse >= mean_squared_error_) {
        best_parameters_[i] -= 2 * parameter_change[i];
        mse = error_fcn(best_parameters_);
      }
      if (mse < mean_squared_error_) {
        mean_squared_error_ = mse;
        parameter_change[i] *= up_factor_;
      } else {
        best_parameters_[i] += parameter_change[i];
        parameter_change[i] *= down_factor_;
      }
    }
  }
}

double CoordinateDescent::Norm(const std::vector<double>& parameter_change) {
  auto sum = 0.0;
  for (const auto& dp : parameter_change) {
    sum += dp;
  }
  return sum;
}
