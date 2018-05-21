// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../JsonVariant.hpp"
#include "../Polyfills/type_traits.hpp"
#include "./endianess.hpp"

namespace ArduinoJson {
namespace Internals {

template <typename Destination>
class MsgPackVisitor {
 public:
  MsgPackVisitor(Destination* output) : _output(output) {}

  template <typename T>
  typename enable_if<sizeof(T) == 4>::type acceptFloat(T value32) {
    writeByte(0xCA);
    writeInteger(value32);
  }

  template <typename T>
  typename enable_if<sizeof(T) == 8>::type acceptFloat(T value64) {
    float value32 = float(value64);
    if (value32 == value64) {
      writeByte(0xCA);
      writeInteger(value32);
    } else {
      writeByte(0xCB);
      writeInteger(value64);
    }
  }

  void acceptArray(const JsonArray& array) {
    writeByte(uint8_t(0x90 + array.size()));
    for (JsonArray::const_iterator it = array.begin(); it != array.end();
         ++it) {
      it->visit(*this);
    }
  }

  void acceptObject(const JsonObject& /*object*/) {}

  void acceptString(const char* value) {
    if (!value) {
      return writeByte(0xC0);
    }

    size_t n = strlen(value);

    if (n < 0x20) {
      writeByte(uint8_t(0xA0 + n));
    } else if (n < 0x100) {
      writeByte(uint8_t(0xD9));
      writeInteger(uint8_t(n));
    } else if (n < 0x10000) {
      writeByte(uint8_t(0xDA));
      writeInteger(uint16_t(n));
    } else {
      writeByte(uint8_t(0xDB));
      writeInteger(uint32_t(n));
    }
    writeBytes(reinterpret_cast<const uint8_t*>(value), n);
  }

  void acceptRawJson(const char* /*value*/) {}

  void acceptNegativeInteger(JsonUInt value) {
    JsonUInt negated = JsonUInt(~value + 1);
    if (value <= 0x20) {
      writeInteger(int8_t(negated));
    } else if (value <= 0x80) {
      writeByte(0xD0);
      writeInteger(int8_t(negated));
    } else if (value <= 0x8000) {
      writeByte(0xD1);
      writeInteger(int16_t(negated));
    } else if (value <= 0x80000000) {
      writeByte(0xD2);
      writeInteger(int32_t(negated));
    }
#if ARDUINOJSON_USE_LONG_LONG || ARDUINOJSON_USE_INT64
    else {
      writeByte(0xD3);
      writeInteger(int64_t(negated));
    }
#endif
  }

  void acceptPositiveInteger(JsonUInt value) {
    if (value <= 0x7F) {
      writeInteger(uint8_t(value));
    } else if (value <= 0xFF) {
      writeByte(0xCC);
      writeInteger(uint8_t(value));
    } else if (value <= 0xFFFF) {
      writeByte(0xCD);
      writeInteger(uint16_t(value));
    } else if (value <= 0xFFFFFFFF) {
      writeByte(0xCE);
      writeInteger(uint32_t(value));
    }
#if ARDUINOJSON_USE_LONG_LONG || ARDUINOJSON_USE_INT64
    else {
      writeByte(0xCF);
      writeInteger(uint64_t(value));
    }
#endif
  }

  void acceptBoolean(bool value) {
    _output->push_back(static_cast<char>(value ? 0xC3 : 0xC2));
  }

  void acceptUndefined() {
    writeByte(0xC0);
  }

 private:
  void writeByte(uint8_t c) {
    _output->push_back(char(c));
  }

  void writeBytes(const uint8_t* c, size_t n) {
    for (; n > 0; --n, ++c) writeByte(*c);
  }

  template <typename T>
  void writeInteger(T value) {
    fixEndianess(value);
    writeBytes(reinterpret_cast<uint8_t*>(&value), sizeof(value));
  }

  Destination* _output;
};  // namespace Internals
}  // namespace Internals

template <typename Destination>
inline size_t serializeMsgPack(const JsonVariant& variant,
                               Destination& output) {
  variant.visit(Internals::MsgPackVisitor<Destination>(&output));
  return output.size();
}

}  // namespace ArduinoJson
