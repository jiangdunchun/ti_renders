#include <meta.h>

#include "D:/code/ti_renders/tests/meta.test/src/meta_test.hpp"

template<>
json meta::Serializer::toJson(MetaTest1 &instance);
template<>
void meta::Serializer::fromJson(const json &json_context, MetaTest1 &instance);

template<>
json meta::Serializer::toJson(MetaTest2 &instance);
template<>
void meta::Serializer::fromJson(const json &json_context, MetaTest2 &instance);

template<>
json meta::Serializer::toJson(MetaTest3 &instance);
template<>
void meta::Serializer::fromJson(const json &json_context, MetaTest3 &instance);

