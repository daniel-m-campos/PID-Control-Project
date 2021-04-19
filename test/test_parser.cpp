#include "gtest/gtest.h"
#include "parser.h"

TEST(ParserTests, TestReadJson) {
  auto j = parser::Read("data/message.json");
  ASSERT_FALSE(j.empty());
}

TEST(ParserTests, TestParseMessage) {
  auto j = parser::Read("data/message.json");
  auto actual = parser::ParseMessage(j);
  SensorData expected{0.7598, 0.1000, 0.0200, 0.00300};
  ASSERT_EQ(actual, expected);
}