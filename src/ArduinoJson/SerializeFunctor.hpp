// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "./Print/DummyPrint.hpp"
#include "./Print/DynamicStringBuilder.hpp"
#include "./Print/StaticStringBuilder.hpp"

#if ARDUINOJSON_ENABLE_STD_STREAM
#include "./Print/StreamPrintAdapter.hpp"
#endif

namespace ArduinoJson {
namespace Internals {

template <template <typename> class TSerializer>
class SerializeFunctor {
 public:
  template <typename TSource, typename TPrint>
  typename enable_if<!StringTraits<TPrint>::has_append, size_t>::type
  operator()(const TSource &source, TPrint &destination) {
    return serialize(source, destination);
  }

#if ARDUINOJSON_ENABLE_STD_STREAM
  template <typename TSource>
  size_t operator()(const TSource &source, std::ostream &os) {
    StreamPrintAdapter adapter(os);
    return serialize(source, adapter);
  }
#endif

  template <typename TSource>
  size_t operator()(const TSource &source, char *buffer, size_t bufferSize) {
    StaticStringBuilder sb(buffer, bufferSize);
    return serialize(source, sb);
  }

  template <typename TSource, size_t N>
  size_t operator()(const TSource &source, char (&buffer)[N]) {
    StaticStringBuilder sb(buffer, N);
    return serialize(source, sb);
  }

  template <typename TSource, typename TDestination>
  typename enable_if<StringTraits<TDestination>::has_append, size_t>::type
  operator()(const TSource &source, TDestination &str) {
    DynamicStringBuilder<TDestination> sb(str);
    return serialize(source, sb);
  }

 private:
  template <typename TSource, typename TPrint>
  size_t serialize(const TSource &source, TPrint &destination) const {
    TSerializer<TPrint> serializer(destination);
    source.visit(serializer);
    return serializer.bytesWritten();
  }
};

}  // namespace Internals
}  // namespace ArduinoJson
