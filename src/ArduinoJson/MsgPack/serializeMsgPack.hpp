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
    _output->push_back(char(0xC0));
  }

  void acceptRawJson(const char* /*value*/) {}

  void acceptNegativeInteger(JsonUInt value) {
    _output->push_back(char(~value + 1));
  }

  void acceptPositiveInteger(JsonUInt value) {
    if (value < 128)
      _output->push_back(char(value));
    else {
      write(0xCC);
      write(uint8_t(value));
    }
  }

  void acceptBoolean(bool value) {
    _output->push_back(static_cast<char>(value ? 0xC3 : 0xC2));
  }

  void acceptUndefined() {
    _output->push_back(char(0xC0));
  }

 private:
  void write(uint8_t c) {
    _output->push_back(char(c));
  }

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
