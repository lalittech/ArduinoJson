// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

template <size_t N>
void check(JsonArray& array, const char (&expected_data)[N]) {
  const size_t expected_len = N - 1;
  std::vector<char> expected(expected_data, expected_data + expected_len);
  std::vector<char> actual;
  size_t len = serializeMsgPack(array, actual);
  CAPTURE(array);
  REQUIRE(len == expected_len);
  REQUIRE(actual == expected);
}

TEST_CASE("serialize MsgPack array") {
  DynamicJsonDocument doc;
  JsonArray& array = doc.to<JsonArray>();

  SECTION("empty") {
    check(array, "\x90");
  }

  SECTION("fixarray") {
    array.add("hello");
    array.add("world");

    check(array, "\x92\xA5hello\xA5world");
  }
}
