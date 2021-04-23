#include "uws_utils.h"

#include "parser.h"

void uws_utils::ResetSimulator(uWS::WebSocket<uWS::SERVER> ws) {
  std::cout << "Resetting Simulator\n";
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}

std::unique_ptr<uWS::Hub> uws_utils::CreateHub(int port) {
  auto hub = std::make_unique<uWS::Hub>();
  hub->onConnection([](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });
  hub->onDisconnection([](uWS::WebSocket<uWS::SERVER> ws, int code,
                          char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected\n";
  });
  if (hub->listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    throw std::runtime_error("Failed to listen to port: " +
                             std::to_string(port));
  }
  return hub;
}

uws_utils::handler uws_utils::CreateMainHandler(PID &steer_pid,
                                                double throttle) {
  using namespace internal;
  return [&steer_pid, throttle](uWS::WebSocket<uWS::SERVER> ws, char *data,
                                size_t length, uWS::OpCode opCode) {
    if (IsMessageEvent(length, data)) {
      auto s = parser::HasData(std::string(data).substr(0, length));
      if (!s.empty()) {
        auto j = json::parse(s);
        auto event = j[0].get<std::string>();
        if (event == "telemetry") {
          auto msg =
              CreateMessage(parser::ParseMessage(j[1]), steer_pid, throttle);
          std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }
      } else {
        // Manual driving
        std::string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }
  };
}

uws_utils::handler uws_utils::CreateMainHandler(Controller &controller) {
  using namespace internal;
  return [&controller](uWS::WebSocket<uWS::SERVER> ws, char *data,
                       size_t length, uWS::OpCode opCode) {
    if (IsMessageEvent(length, data)) {
      auto s = parser::HasData(std::string(data).substr(0, length));
      if (!s.empty()) {
        auto j = json::parse(s);
        auto event = j[0].get<std::string>();
        if (event == "telemetry") {
          auto msg = CreateMessage(parser::ParseMessage(j[1]), controller);
          std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }
      } else {
        // Manual driving
        std::string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }
  };
}
uws_utils::handler uws_utils::CreateSimulationHandler(PID &steer_pid,
                                                      size_t max_steps,
                                                      double throttle) {
  using namespace internal;
  size_t counter = 0;
  return [&steer_pid, &max_steps, counter, throttle](
             uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length,
             uWS::OpCode opCode) mutable {
    std::cout << "counter=" << counter << std::endl;
    if (counter >= max_steps) {
      ResetSimulator(ws);
      return;
    }
    if (IsMessageEvent(length, data)) {
      auto s = parser::HasData(std::string(data).substr(0, length));
      if (s.empty()) return;
      auto j = json::parse(s);
      auto event = j[0].get<std::string>();
      if (event != "telemetry") return;
      auto msg = CreateMessage(parser::ParseMessage(j[1]), steer_pid, throttle);
      ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      ++counter;
    }
  };
}

bool uws_utils::internal::IsMessageEvent(size_t length, const char *data) {
  return length > 2 && data[0] == '4' && data[1] == '2';
}

std::string uws_utils::internal::CreateMessage(SensorData sensor_data,
                                               PID &steer_pid,
                                               double throttle) {
  std::cout << sensor_data << std::endl;
  steer_pid.UpdateError(sensor_data.cross_track_error);
  auto error = steer_pid.TotalError();
  auto steering_angle = -std::clamp(error, -1.0, 1.0);
  json msgJson;
  msgJson["steering_angle"] = steering_angle;
  msgJson["throttle"] = throttle;
  auto msg = "42[\"steer\"," + msgJson.dump() + "]";
  std::cout << msg << std::endl;
  return msg;
}

std::string uws_utils::internal::CreateMessage(SensorData sensor_data,
                                               Controller &controller) {
  std::cout << sensor_data << std::endl;
  auto controls = controller(sensor_data);
  json msgJson;
  msgJson["steering_angle"] = controls.steering_angle;
  msgJson["throttle"] = controls.throttle;
  auto msg = "42[\"steer\"," + msgJson.dump() + "]";
  std::cout << msg << std::endl;
  return msg;
}

uws_utils::Simulation::Simulation(PID &steer_pid, size_t max_steps,
                                  double throttle)
    : steer_pid_{steer_pid},
      max_steps_{max_steps},
      throttle_{throttle},
      counter_{0} {}

void uws_utils::Simulation::operator()(uWS::WebSocket<uWS::SERVER> ws,
                                       char *data, size_t length,
                                       uWS::OpCode code) {
  using namespace internal;
  std::cout << "counter=" << counter_ << std::endl;
  if (counter_ >= max_steps_) {
    counter_ = 0;
    ResetSimulator(ws);
    throw UWSUtilsException();
  }
  if (IsMessageEvent(length, data)) {
    auto s = parser::HasData(std::string(data).substr(0, length));
    if (s.empty()) return;
    json j;
    try {
      j = json::parse(s);
    } catch (const std::invalid_argument &e) {
      return;
    }
    auto event = j[0].get<std::string>();
    if (event != "telemetry") return;
    auto msg = CreateMessage(parser::ParseMessage(j[1]), steer_pid_, throttle_);
    ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
    ++counter_;
  }
}