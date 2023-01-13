#ifndef META_TEST_SERIALIZER_TEST_HPP_
#define META_TEST_SERIALIZER_TEST_HPP_

#include <serializer.h>

#include <string>

class SerializerTest1 {
public:
    char         char_var_;
    int          int_var_;
    unsigned int unsigned_int_var_;

    SerializerTest1(char char_var, int int_var, unsigned int unsigned_int_var) {
        char_var_         = char_var;
        int_var_          = int_var;
        unsigned_int_var_ = unsigned_int_var;
    }
    SerializerTest1() {}
};

class SerializerTest2 {
public:
    float       float_var_;
    double      double_var_;
    bool        bool_var_;
    std::string string_var_;

    SerializerTest2(float float_var, double double_var, bool bool_var, std::string string_var) {
        float_var_  = float_var;
        double_var_ = double_var;
        bool_var_   = bool_var;
        string_var_ = string_var;
    }
    SerializerTest2() {}
};

class SerializerTest3 {
public:
    SerializerTest1 serializer_test_1_var_;
    SerializerTest2 serializer_test_2_var_;

    SerializerTest3(SerializerTest1 serializer_test_1_var, SerializerTest2 serializer_test_2_var) {
        serializer_test_1_var_ = serializer_test_1_var;
        serializer_test_2_var_ = serializer_test_2_var;
    }
    SerializerTest3() {}
};

/* auto generated code */
template<>
json meta::Serializer::toJson(SerializerTest1 &instance) {
    json::object ret;
    ret["char_var_"]         = toJson(instance.char_var_);
    ret["int_var_"]          = toJson(instance.int_var_);
    ret["unsigned_int_var_"] = toJson(instance.unsigned_int_var_);
    return ret;
}
template<>
void meta::Serializer::fromJson(const json &json_context, SerializerTest1 &instance) {
    fromJson(json_context["char_var_"], instance.char_var_);
    fromJson(json_context["int_var_"], instance.int_var_);
    fromJson(json_context["unsigned_int_var_"], instance.unsigned_int_var_);
}
template<>
json meta::Serializer::toJson(SerializerTest2 &instance) {
    json::object ret;
    ret["float_var_"]  = toJson(instance.float_var_);
    ret["double_var_"] = toJson(instance.double_var_);
    ret["bool_var_"]   = toJson(instance.bool_var_);
    ret["string_var_"] = toJson(instance.string_var_);

    return ret;
}
template<>
void meta::Serializer::fromJson(const json &json_context, SerializerTest2 &instance) {
    fromJson(json_context["float_var_"], instance.float_var_);
    fromJson(json_context["double_var_"], instance.double_var_);
    fromJson(json_context["bool_var_"], instance.bool_var_);
    fromJson(json_context["string_var_"], instance.string_var_);
}
template<>
json meta::Serializer::toJson(SerializerTest3 &instance) {
    json::object ret;
    ret["serializer_test_1_var_"] = toJson(instance.serializer_test_1_var_);
    ret["serializer_test_2_var_"] = toJson(instance.serializer_test_2_var_);

    return ret;
}
template<>
void meta::Serializer::fromJson(const json &json_context, SerializerTest3 &instance) {
    fromJson(json_context["serializer_test_1_var_"], instance.serializer_test_1_var_);
    fromJson(json_context["serializer_test_2_var_"], instance.serializer_test_2_var_);
}

#endif // !META_TEST_SERIALIZER_TEST_HPP_
