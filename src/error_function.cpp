#include "error_function.h"

#include "uws_utils.h"

error_function::Simulation::Simulation(uWS::Hub& hub, PID& steer_pid,
                                       size_t max_steps, double throttle)
    : steer_pid_{steer_pid},
      hub_{hub},
      max_steps_{max_steps},
      handler_{uws_utils::Simulation(steer_pid_, max_steps_, throttle)} {
  hub_.onMessage(handler_);
}

double error_function::Simulation::operator()(std::vector<double> parameters) {
  std::cout << "Computing error...\n";
  steer_pid_.Reset(parameters[0], parameters[1], parameters[2]);
  try {
    // FIXME::This was the only way I could think of to break out of the run
    //  loop.
    hub_.run();
  } catch (const uws_utils::UWSUtilsException& e) {
    std::cout << "Completed a simulation run!\n";
    std::cout << "MSE=" << steer_pid_.MeanSquaredError() << "\n";
    std::cout << "Kp=" << parameters[0] << " Ki=" << parameters[1]
              << " Kd=" << parameters[2] << "\n";
  }
  return steer_pid_.MeanSquaredError();
}

std::function<double(const std::vector<double>&)> error_function::Create(
    uWS::Hub& hub, PID& steer_pid, size_t max_steps) {
  auto error_fcn = [&hub, &steer_pid, &max_steps](
                       const std::vector<double>& parameters) -> double {
    std::cout << "Computing error...\n";
    steer_pid.Reset(parameters[0], parameters[1], parameters[2]);
    hub.onMessage(uws_utils::Simulation(steer_pid, max_steps));
    hub.run();
    return steer_pid.MeanSquaredError();
  };
  return error_fcn;
}
