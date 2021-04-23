#ifndef ERROR_FUNCTION_H
#define ERROR_FUNCTION_H

#include <uWS/Hub.h>

#include <vector>

#include "pid.h"
#include "uws_utils.h"

namespace error_function {

class ErrorFunction {
 public:
  virtual ~ErrorFunction() = default;
  virtual double operator()(std::vector<double> parameters) = 0;
};

class Simulation : public ErrorFunction {
 public:
  Simulation(uWS::Hub& hub, PID& steer_pid, size_t max_steps, double throttle);
  double operator()(std::vector<double> parameters) override;

 private:
  PID& steer_pid_;
  uWS::Hub& hub_;
  size_t max_steps_;
  uws_utils::Simulation handler_;
};

std::function<double(const std::vector<double>&)> Create(uWS::Hub& hub,
                                                         PID& steer_pid,
                                                         size_t max_steps);

}  // namespace error_function

#endif  // ERROR_FUNCTION_H
