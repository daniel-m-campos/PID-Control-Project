#include <string>

#include "controller.h"
#include "json.hpp"
#include "pid.h"
#include "uws_utils.h"

using nlohmann::json;
using std::string;

constexpr int kPort = 4567;

int main() {
  PID steer_pid(0.08, 0.0, 3.0);
  PID throttle_pid(0.2, 0.0, 3.0);
  Controller controller(steer_pid, throttle_pid, 200.0, 1.7);
  auto hub = uws_utils::CreateHub(kPort);
  hub->onMessage(uws_utils::CreateMainHandler(controller));
  hub->run();
}