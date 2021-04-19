#include "gtest/gtest.h"
#include "pid.h"

TEST(PIDTests, TestTotalError) {
  PID pid(1, 2, 3);
  auto cte = 0.7;
  pid.UpdateError(cte);
  auto actual = pid.TotalError();
  auto expected = cte * (1 + 2 + 3);
  ASSERT_NEAR(actual, expected, 1e-6);
}