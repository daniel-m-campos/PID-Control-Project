#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "datamodels.h"
#include "pid.h"

class Controller {
 public:
  Controller(PID& steer_pid, PID& throttle_pid, double target_speed,
             double cte_speed_discount);
  struct Output {
    double steering_angle;
    double throttle;
  };
  Output operator()(const SensorData& input);

 private:
  PID& steer_pid_;
  PID& throttle_pid_;
  double target_speed_;
  double cte_speed_discount_;
  double ComputeSteeringAngle() const;
  double ComputeThrottle() const;
};

#endif  // CONTROLLER_H
