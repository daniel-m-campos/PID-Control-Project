#include <cmath>

#include "gtest/gtest.h"
#include "learner.h"

TEST(LearnerTests, TestCoordinateDescent) {
  const double target_x = 1.0;
  const double target_y = 2.0;
  auto simulator = [&target_x, &target_y](const auto& xy) {
    return pow(target_x - xy[0], 2) + pow(target_y - xy[1], 2);
  };
  std::vector<double> initial_parameters{1.0, 2.0};
  std::vector<double> parameter_perturbations{0.25, 0.25};
  CoordinateDescent learner{simulator, initial_parameters,
                            parameter_perturbations, 0.000001};
  learner.Learn();
  auto best_parameters = learner.BestParameters();
  const auto abs_error = 1e-6;
  ASSERT_NEAR(best_parameters[0], target_x, abs_error);
  ASSERT_NEAR(best_parameters[1], target_y, abs_error);
  auto mse = learner.MeanSquaredError();
  ASSERT_NEAR(mse, 0.0, abs_error);
}