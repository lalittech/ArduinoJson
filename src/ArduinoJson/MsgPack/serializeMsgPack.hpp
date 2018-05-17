// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../JsonVariant.hpp"

namespace ArduinoJson {

template <typename Destination>
inline size_t serializeMsgPack(const JsonVariant& variant,
                               Destination& output) {
  output.push_back(variant.as<char>());

  return output.size();
}

}  // namespace ArduinoJson
