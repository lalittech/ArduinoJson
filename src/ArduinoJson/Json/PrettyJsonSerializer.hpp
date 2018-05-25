// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../Serialization/measure.hpp"
#include "../Serialization/serialize.hpp"
#include "./IndentedPrint.hpp"
#include "./JsonSerializer.hpp"
#include "./Prettyfier.hpp"

namespace ArduinoJson {
namespace Internals {

template <typename TPrint>
class PrettyJsonSerializer : public IndentedPrint<TPrint>,
                             public Prettyfier<TPrint>,
                             public JsonSerializer<Prettyfier<TPrint> > {
 public:
  PrettyJsonSerializer(TPrint &output)
      : IndentedPrint<TPrint>(output),
        Prettyfier<TPrint>(static_cast<IndentedPrint<TPrint> &>(*this)),
        JsonSerializer<Prettyfier<TPrint> >(
            static_cast<Prettyfier<TPrint> &>(*this)) {}

 private:
};
}  // namespace Internals

template <typename TSource, typename TDestination>
size_t serializeJsonPretty(TSource &source, TDestination &destination) {
  using namespace Internals;
  return serialize<PrettyJsonSerializer>(source, destination);
}

template <typename TSource>
size_t serializeJsonPretty(const TSource &source, char *buffer,
                           size_t bufferSize) {
  using namespace Internals;
  return serialize<PrettyJsonSerializer>(source, buffer, bufferSize);
}

template <typename TSource>
size_t measureJsonPretty(const TSource &source) {
  using namespace Internals;
  return measure<PrettyJsonSerializer>(source);
}

}  // namespace ArduinoJson
