// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

template <size_t N>
void check(JsonVariant variant, const char (&expected_data)[N]) {
  const size_t expected_len = N - 1;
  std::vector<char> expected(expected_data, expected_data + expected_len);
  std::vector<char> actual;
  size_t len = serializeMsgPack(variant, actual);
  REQUIRE(len == expected_len);
  REQUIRE(actual == expected);
}

TEST_CASE("serialize MsgPack value") {
  SECTION("undefined") {
    check(JsonVariant(), "\xC0");  // we represent undefined as nil
  }

  SECTION("nil") {
    const char* nil = 0;  // ArduinoJson uses a string for null
    check(nil, "\xC0");
  }

  SECTION("bool") {
    check(false, "\xC2");
    check(true, "\xC3");
  }

  SECTION("positive fixint") {
    check(0, "\x00");
    check(127, "\x7F");
  }

  SECTION("negative fixint") {
    check(-32, "\xE0");
    check(-1, "\xFF");
  }

  SECTION("uint 8") {
    check(128, "\xCC\x80");
    check(255, "\xCC\xFF");
  }

  SECTION("uint 16") {
    check(256, "\xCD\x01\x00");
    check(65535, "\xCD\xFF\xFF");
  }
}
