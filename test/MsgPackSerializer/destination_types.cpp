// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("serialize MsgPack to various destination types") {
  DynamicJsonDocument doc;
  JsonObject &object = doc.to<JsonObject>();
  object["hello"] = "world";

  SECTION("std::string") {
    std::string result;
    serializeMsgPack(object, result);

    REQUIRE("\x81\xA5hello\xA5world" == result);
  }
}
