#include <string>

#include "error_function.h"
#include "json.hpp"
#include "learner.h"
#include "pid.h"
#include "uws_utils.h"

using nlohmann::json;
using std::string;

constexpr int kPort = 4567;

int main() {
  PID steer_pid(0.0, 0.0, 0.0);
  auto hub = uws_utils::CreateHub(kPort);
  auto error_fcn = error_function::Simulation(*hub, steer_pid, 10'000, 0.3);
  CoordinateDescent learner{
      error_fcn,
      {0.08, 0.0, 3.0},
      {0.01, 0.0, 0.00},
      0.00001,
  };
  learner.Learn();
  std::cout << "MSE: " << learner.MeanSquaredError() << std::endl;
  auto best_parameters = learner.BestParameters();
}