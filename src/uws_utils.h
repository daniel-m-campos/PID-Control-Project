#ifndef UWS_UTILS_H
#define UWS_UTILS_H

#include <uWS/uWS.h>

#include "controller.h"
#include "datamodels.h"
#include "pid.h"

namespace uws_utils {

class Handler {
 public:
  virtual ~Handler() = default;
  virtual void operator()(uWS::WebSocket<uWS::SERVER>, char*, size_t,
                          uWS::OpCode) = 0;
};

class Simulation : public Handler {
 public:
  Simulation(PID& steer_pid, size_t max_steps, double throttle = 1.0);
  void operator()(uWS::WebSocket<uWS::SERVER> ws, char* data, size_t length,
                  uWS::OpCode code) override;

 private:
  PID& steer_pid_;
  size_t max_steps_;
  double throttle_;
  int counter_;
};

struct UWSUtilsException : public std::exception {
  const char* what() const throw() { return "uws_utils exception"; }
};

using handler = std::function<void(uWS::WebSocket<uWS::SERVER>, char*, size_t,
                                   uWS::OpCode)>;

std::unique_ptr<uWS::Hub> CreateHub(int port);

void ResetSimulator(uWS::WebSocket<uWS::SERVER> ws);

handler CreateMainHandler(PID& steer_pid, double throttle = 0.3);

handler CreateMainHandler(Controller& controller);

handler CreateSimulationHandler(PID& steer_pid, size_t max_steps,
                                double throttle = 0.3);

namespace internal {

bool IsMessageEvent(size_t length, const char* data);

std::string CreateMessage(SensorData sensor_data, PID& steer_pid,
                          double throttle);

std::string CreateMessage(SensorData sensor_data, Controller& controller);

}  // namespace internal

}  // namespace uws_utils

#endif  // UWS_UTILS_H
