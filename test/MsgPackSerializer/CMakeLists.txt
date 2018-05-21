# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2018
# MIT License

add_executable(MsgPackSerializerTests
	serializeArray.cpp
	serializeVariant.cpp
)

target_link_libraries(MsgPackSerializerTests catch)
add_test(MsgPackSerializer MsgPackSerializerTests)
