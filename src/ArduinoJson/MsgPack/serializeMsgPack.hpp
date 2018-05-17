// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../JsonVariant.hpp"

namespace ArduinoJson {
namespace Internals {

template <typename Destination>
class MsgPackVisitor {
 public:
  MsgPackVisitor(Destination* output) : _output(output) {}

  void acceptFloat(JsonFloat /*value*/) {}

  void acceptArray(const JsonArray& /*array*/) {}

  void acceptObject(const JsonObject& /*object*/) {}

  void acceptString(const char* /*value*/) {
    _output->push_back(static_cast<char>(0xC0));
  }

  void acceptRawJson(const char* /*value*/) {}

  void acceptNegativeInteger(JsonUInt value) {
    _output->push_back(static_cast<char>(-value));
  }

  void acceptPositiveInteger(JsonUInt value) {
    _output->push_back(static_cast<char>(value));
  }

  void acceptBoolean(bool /*value*/) {}

  void acceptUndefined() {}

 private:
  Destination* _output;
};
}  // namespace Internals

template <typename Destination>
inline size_t serializeMsgPack(const JsonVariant& variant,
                               Destination& output) {
  variant.visit(Internals::MsgPackVisitor<Destination>(&output));
  return output.size();
}

}  // namespace ArduinoJson
