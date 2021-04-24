#include "controller.h"

#include <algorithm>

Controller::Controller(PID& steer_pid, PID& throttle_pid, double target_speed,
                       double cte_speed_discount)
    : steer_pid_(steer_pid),
      throttle_pid_(throttle_pid),
      target_speed_(target_speed),
      cte_speed_discount_{cte_speed_discount} {}

Controller::Output Controller::operator()(const SensorData& input) {
  steer_pid_.UpdateError(input.cross_track_error);
  auto target_speed =
      target_speed_ /
      (1 + cte_speed_discount_ * std::abs(input.cross_track_error));
  throttle_pid_.UpdateError(input.speed - target_speed);
  return Output{ComputeSteeringAngle(), ComputeThrottle()};
}

double Controller::ComputeSteeringAngle() const {
  auto error = steer_pid_.TotalError();
  return -std::clamp(error, -1.0, 1.0);
}
double Controller::ComputeThrottle() const {
  auto speed_error = -throttle_pid_.TotalError();
  return speed_error / (1 + abs(speed_error));
}
