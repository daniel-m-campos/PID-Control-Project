#include <string>

#include "json.hpp"
#include "pid.h"
#include "uws_utils.h"

using nlohmann::json;
using std::string;

constexpr int kPort = 4567;

int main() {
  PID pid(0.01, 0.0, 0.0);
  auto hub = uws_utils::CreateHub(kPort);
  hub->onMessage(uws_utils::CreateMainHandler(pid));
  hub->run();
}