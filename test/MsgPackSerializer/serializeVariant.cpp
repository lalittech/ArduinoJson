// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

size_t serializeMsgPack(const JsonVariant&, std::string& output) {
  output.push_back(0);
  return 1;
}

TEST_CASE("serialize MsgPack value") {
  JsonVariant variant = 0;

  std::string output;
  size_t len = serializeMsgPack(variant, output);
  REQUIRE(len == 1);
  REQUIRE(output.size() == 1);
  REQUIRE(output[0] == 0);
}
