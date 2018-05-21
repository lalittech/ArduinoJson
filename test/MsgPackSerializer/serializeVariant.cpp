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
  CAPTURE(variant);
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

  SECTION("uint 8") {
    check(128, "\xCC\x80");
    check(255, "\xCC\xFF");
  }

  SECTION("uint 16") {
    check(256, "\xCD\x01\x00");
    check(0xFFFF, "\xCD\xFF\xFF");
  }

  SECTION("uint 32") {
    check(0x00010000U, "\xCE\x00\x01\x00\x00");
    check(0x12345678U, "\xCE\x12\x34\x56\x78");
    check(0xFFFFFFFFU, "\xCE\xFF\xFF\xFF\xFF");
  }

#if ARDUINOJSON_USE_LONG_LONG || ARDUINOJSON_USE_INT64
  SECTION("uint 64") {
    check(0x0001000000000000U, "\xCF\x00\x01\x00\x00\x00\x00\x00\x00");
    check(0x123456789ABCDEF0U, "\xCF\x12\x34\x56\x78\x9A\xBC\xDE\xF0");
    check(0xFFFFFFFFFFFFFFFFU, "\xCF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF");
  }
#endif

  SECTION("negative fixint") {
    check(-1, "\xFF");
    check(-32, "\xE0");
  }

  SECTION("int 8") {
    check(-33, "\xD0\xDF");
    check(-128, "\xD0\x80");
  }

  SECTION("int 16") {
    check(-129, "\xD1\xFF\x7F");
    check(-32768, "\xD1\x80\x00");
  }

  SECTION("int 32") {
    check(-32769, "\xD2\xFF\xFF\x7F\xFF");
    check(-2147483647 - 1, "\xD2\x80\x00\x00\x00");
  }

#if ARDUINOJSON_USE_LONG_LONG || ARDUINOJSON_USE_INT64
  SECTION("int 64") {
    check(int64_t(0xFEDCBA9876543210), "\xD3\xFE\xDC\xBA\x98\x76\x54\x32\x10");
  }
#endif

  SECTION("float 32") {
    check(1.25, "\xCA\x3F\xA0\x00\x00");
  }

  SECTION("float 64") {
    check(3.1415, "\xCB\x40\x09\x21\xCA\xC0\x83\x12\x6F");
  }

  SECTION("fixstr") {
    check("", "\xA0");
    check("hello world hello world hello !",
          "\xBFhello world hello world hello !");
  }

  SECTION("str 8") {
    check("hello world hello world hello !!",
          "\xD9\x20hello world hello world hello !!");
  }
}
