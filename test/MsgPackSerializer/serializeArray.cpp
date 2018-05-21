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

  SECTION("array 16") {
    for (int i = 0; i < 16; i++) array.add(i);

    check(array,
          "\xDC\x00\x10\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D"
          "\x0E\x0F");
  }
}
