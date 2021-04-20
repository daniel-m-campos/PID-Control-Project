#include "gtest/gtest.h"
#include "pid.h"

TEST(PIDTests, TestUpdateError) {
  const auto Kp = 1;
  const auto Ki = 2;
  const auto Kd = 3;
  PID pid(Kp, Ki, Kd);
  auto cte = 0.7;
  pid.UpdateError(cte);
  pid.UpdateError(cte);
  auto actual = pid.TotalError();
  auto expected = cte * (Kp + 2 * Ki + 0 * Kd);
  ASSERT_NEAR(actual, expected, 1e-6);
  ASSERT_NEAR(pid.MeanSquaredError(), cte * cte, 1e-6);
}