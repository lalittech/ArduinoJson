// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("serialize MsgPack to various destination types") {
  DynamicJsonDocument doc;
  JsonObject &object = doc.to<JsonObject>();
  object["hello"] = "world";
  const char *expected_result = "\x81\xA5hello\xA5world";

  SECTION("std::string") {
    std::string result;
    serializeMsgPack(object, result);

    REQUIRE(expected_result == result);
  }

  /*  SECTION("std::vector<char>") {
      std::vector<char> result;
      serializeMsgPack(object, result);

      REQUIRE(std::vector<char>(expected_result, expected_result + 13) ==
    result);
    } */

  SECTION("char[]") {
    char result[64];
    serializeMsgPack(object, result);

    REQUIRE(std::string(expected_result) == result);
  }

  SECTION("char*") {
    char result[64];
    serializeMsgPack(object, result, 64);

    REQUIRE(std::string(expected_result) == result);
  }
}
