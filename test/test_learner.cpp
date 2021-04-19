#include "gtest/gtest.h"
#include "learner.h"

TEST(LearnerTests, TestCoordinateDescent) {
  auto simulator = [](const auto& xy) { return pow(xy[0], 2) + pow(xy[1], 2); };
  std::vector<double> initial_parameters{1.0, 2.0};
  std::vector<double> parameter_perturbations{0.25, 0.25};
  CoordinateDescent learner{simulator, initial_parameters,
                            parameter_perturbations, 0.000001};
  learner.Learn();
  auto best_parameters = learner.BestParameters();
  const auto abs_error = 1e-6;
  ASSERT_NEAR(best_parameters[0], 0.0, abs_error);
  ASSERT_NEAR(best_parameters[1], 0.0, abs_error);
  auto mse = learner.MeanSquaredError();
  ASSERT_NEAR(mse, 0.0, abs_error);
}