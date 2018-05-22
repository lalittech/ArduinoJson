// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

static void check(const JsonObject& object, const char* expected_data,
                  size_t expected_len) {
  std::vector<char> expected(expected_data, expected_data + expected_len);
  std::vector<char> actual;
  size_t len = serializeMsgPack(object, actual);
  CAPTURE(object);
  REQUIRE(len == expected_len);
  REQUIRE(actual == expected);
}

template <size_t N>
static void check(const JsonObject& object, const char (&expected_data)[N]) {
  const size_t expected_len = N - 1;
  check(object, expected_data, expected_len);
}

/*static void check(const JsonObject& object, const std::string& expected) {
  check(object, expected.data(), expected.length());
}*/

TEST_CASE("serialize MsgPack object") {
  DynamicJsonDocument doc;
  JsonObject& object = doc.to<JsonObject>();

  SECTION("empty") {
    check(object, "\x80");
  }
}
