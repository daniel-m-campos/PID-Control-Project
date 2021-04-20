#ifndef UWS_UTILS_H
#define UWS_UTILS_H

#include <uWS/uWS.h>

#include "datamodels.h"
#include "pid.h"

namespace uws_utils {
using Handler = std::function<void(uWS::WebSocket<uWS::SERVER>, char*, size_t,
                                   uWS::OpCode)>;

std::unique_ptr<uWS::Hub> CreateHub(int port);

void ResetSimulator(uWS::WebSocket<uWS::SERVER> ws);

Handler CreateMainHandler(PID& steer_pid, double throttle = 0.3);

Handler CreateSimulationHandler(PID& steer_pid, size_t max_steps,
                                double throttle = 0.3);

namespace internal {

bool IsMessageEvent(size_t length, const char* data);

std::string CreateMessage(SensorData sensor_data, PID steer_pid,
                          double throttle);

}  // namespace internal

}  // namespace uws_utils

#endif  // UWS_UTILS_H
