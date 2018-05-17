// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

void check(JsonVariant variant, const char* expected, size_t expected_len) {
  std::string output;
  size_t len = serializeMsgPack(variant, output);
  REQUIRE(len == expected_len);
  REQUIRE(output.size() == expected_len);
  REQUIRE(memcmp(expected, output.c_str(), len) == 0);
}

TEST_CASE("serialize MsgPack value") {
  SECTION("positive fixint") {
    check(0, "\x00", 1);
    check(127, "\x7F", 1);
  }
}
