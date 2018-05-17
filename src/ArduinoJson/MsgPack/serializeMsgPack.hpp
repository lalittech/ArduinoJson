// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../JsonVariant.hpp"

namespace ArduinoJson {

inline size_t serializeMsgPack(const JsonVariant& variant,
                               std::string& output) {
  output.push_back(variant.as<char>());

  return output.size();
}

}  // namespace ArduinoJson
