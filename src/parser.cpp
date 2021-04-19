#include "parser.h"

#include <fstream>

std::string parser::HasData(const std::string& s) {
  using std::string;
  auto found_null = s.find("null");
  auto b1 = s.find_first_of('[');
  auto b2 = s.find_last_of(']');
  if (found_null != string::npos) {
    return "";
  } else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

json parser::Read(const std::string& filename) {
  std::ifstream i(filename);
  json j;
  i >> j;
  return j;
}

void parser::Capture(const std::string& filename, const json& j) {
  std::ofstream ofs(filename);
  ofs << std::setw(4) << j << std::endl;
}

SensorData parser::ParseMessage(const json& j) {
  return SensorData{std::stod(j["cte"].get<std::string>()),
                    std::stod(j["speed"].get<std::string>()),
                    std::stod(j["steering_angle"].get<std::string>()),
                    std::stod(j["throttle"].get<std::string>())};
}
