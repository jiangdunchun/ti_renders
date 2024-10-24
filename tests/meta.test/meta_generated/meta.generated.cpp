#include "D:/code/ti_renders/tests/meta.test/meta_generated/meta.generated.h"

template<>
json meta::Serializer::toJson(MetaTest1 &instance) {
json::object ret;
ret["char_var"] = toJson(instance.char_var);
ret["int_var"] = toJson(instance.int_var);
ret["unsigned_int_var"] = toJson(instance.unsigned_int_var);
return ret;
}
template<>
void meta::Serializer::fromJson(const json &json_context, MetaTest1 &instance) {
fromJson(json_context["char_var"], instance.char_var);
fromJson(json_context["int_var"], instance.int_var);
fromJson(json_context["unsigned_int_var"], instance.unsigned_int_var);
}

template<>
json meta::Serializer::toJson(MetaTest2 &instance) {
json::object ret;
ret["float_var"] = toJson(instance.float_var);
ret["double_var"] = toJson(instance.double_var);
ret["bool_var"] = toJson(instance.bool_var);
ret["string_var"] = toJson(instance.string_var);
return ret;
}
template<>
void meta::Serializer::fromJson(const json &json_context, MetaTest2 &instance) {
fromJson(json_context["float_var"], instance.float_var);
fromJson(json_context["double_var"], instance.double_var);
fromJson(json_context["bool_var"], instance.bool_var);
fromJson(json_context["string_var"], instance.string_var);
}

template<>
json meta::Serializer::toJson(MetaTest3 &instance) {
json::object ret;
ret["test_1_var"] = toJson(instance.test_1_var);
ret["test_2_var"] = toJson(instance.test_2_var);
return ret;
}
template<>
void meta::Serializer::fromJson(const json &json_context, MetaTest3 &instance) {
fromJson(json_context["test_1_var"], instance.test_1_var);
fromJson(json_context["test_2_var"], instance.test_2_var);
}

void meta::Reflector::registAll() {
meta::Reflector::registType<MetaTest1>("MetaTest1")
.addField("char_var", &MetaTest1::char_var)
.addField("int_var", &MetaTest1::int_var)
.addField("unsigned_int_var", &MetaTest1::unsigned_int_var);

meta::Reflector::registType<MetaTest2>("MetaTest2")
.addField("float_var", &MetaTest2::float_var)
.addField("double_var", &MetaTest2::double_var)
.addField("bool_var", &MetaTest2::bool_var)
.addField("string_var", &MetaTest2::string_var);

meta::Reflector::registType<MetaTest3>("MetaTest3")
.addField("test_1_var", &MetaTest3::test_1_var)
.addField("test_2_var", &MetaTest3::test_2_var)
.addMethod("get", &MetaTest3::get)
.addMethod("plusandset", &MetaTest3::plusandset);
}