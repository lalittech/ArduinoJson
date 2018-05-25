// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Deserialization/deserialize.hpp"
#include "MsgPack/MsgPackDeserializer.hpp"

namespace ArduinoJson {
template <typename TDocument, typename TString>
DeserializationError deserializeMsgPack(TDocument &doc, const TString &input) {
  using namespace Internals;
  return deserialize<MsgPackDeserializer>(doc, input);
}

template <typename TDocument, typename TChar>
DeserializationError deserializeMsgPack(TDocument &doc, TChar *input,
                                        size_t inputSize) {
  using namespace Internals;
  return deserialize<MsgPackDeserializer>(doc, input, inputSize);
}

template <typename TDocument, typename TInput>
DeserializationError deserializeMsgPack(TDocument &doc, TInput &input) {
  using namespace Internals;
  return deserialize<MsgPackDeserializer>(doc, input);
}
}  // namespace ArduinoJson
