// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

void check(JsonVariant variant, const char* expected_data,
           size_t expected_len) {
  std::vector<char> expected(expected_data, expected_data + expected_len);
  std::vector<char> actual;
  size_t len = serializeMsgPack(variant, actual);
  REQUIRE(len == expected_len);
  REQUIRE(actual == expected);
}

TEST_CASE("serialize MsgPack value") {
  SECTION("nil") {
    const char* nil = 0;  // ArduinoJson uses a string for null
    check(nil, "\xC0", 1);
  }

  SECTION("positive fixint") {
    check(0, "\x00", 1);
    check(127, "\x7F", 1);
  }

  SECTION("negative fixint") {
    check(-32, "\xE0", 1);
    check(-1, "\xFF", 1);
  }
}
