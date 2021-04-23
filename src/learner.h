#ifndef LEARNER_H
#define LEARNER_H

#include <functional>
#include <vector>

class Learner {
 public:
  virtual ~Learner() = default;
  virtual void Learn() = 0;
  virtual const std::vector<double>& BestParameters() const = 0;
  virtual double MeanSquaredError() const = 0;
};

class CoordinateDescent : public Learner {
 public:
  CoordinateDescent(std::function<double(const std::vector<double>&)> error_fcn,
                    std::vector<double> initial_parameters,
                    std::vector<double> parameter_change, double tolerance,
                    double up_factor = 1.1, double down_factor = 0.9);
  void Learn() override;
  const std::vector<double>& BestParameters() const override;
  double MeanSquaredError() const override;

 private:
  std::function<double(const std::vector<double>&)> error_fcn;
  std::vector<double> initial_parameters_;
  std::vector<double> parameter_change_;
  std::vector<double> best_parameters_;
  double up_factor_;
  double down_factor_;
  double tolerance_;
  double mean_squared_error_;
  static double Norm(const std::vector<double>& parameter_change);
};

#endif  // LEARNER_H
