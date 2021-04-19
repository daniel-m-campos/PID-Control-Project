#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "datamodels.h"
#include "json.hpp"

using nlohmann::json;

namespace parser {

std::string HasData(const std::string& s);

void Capture(const std::string& filename, const json& j);

json Read(const std::string& filename);

SensorData ParseMessage(const json& j);

};  // namespace parser

#endif  // PARSER_H
