#include <serializer.h>

#include <string>

class serializer_test_1 {
public:
    char         char_var_;
    int          int_var_;
    unsigned int unsigned_int_var_;

    serializer_test_1(char char_var, int int_var, unsigned int unsigned_int_var) {
        char_var_         = char_var;
        int_var_          = int_var;
        unsigned_int_var_ = unsigned_int_var;
    }
    serializer_test_1() {}
};

class serializer_test_2 {
public:
    float       float_var_;
    double      double_var_;
    bool        bool_var_;
    std::string string_var_;

    serializer_test_2(float float_var, double double_var, bool bool_var, std::string string_var) {
        float_var_   = float_var;
        double_var_  = double_var;
        bool_var_    = bool_var;
        string_var_  = string_var;
    }
    serializer_test_2() {}
};

class serializer_test_3 {
public:
    serializer_test_1 serializer_test_1_var_;
    serializer_test_2 serializer_test_2_var_;

    serializer_test_3(serializer_test_1 serializer_test_1_var, serializer_test_2 serializer_test_2_var) {
        serializer_test_1_var_ = serializer_test_1_var;
        serializer_test_2_var_ = serializer_test_2_var;
    }
    serializer_test_3() {}
};


/* auto generated code */
template<>
json meta::serializer::to_json(serializer_test_1 &instance) {
    json::object ret;
    ret["char_var_"]         = to_json(instance.char_var_);
    ret["int_var_"]          = to_json(instance.int_var_);
    ret["unsigned_int_var_"] = to_json(instance.unsigned_int_var_);
    return ret;
}
template<>
void meta::serializer::from_json(const json &json_context, serializer_test_1 &instance) {
    from_json(json_context["char_var_"], instance.char_var_);
    from_json(json_context["int_var_"], instance.int_var_);
    from_json(json_context["unsigned_int_var_"], instance.unsigned_int_var_);
}
template<>
json meta::serializer::to_json(serializer_test_2 &instance) {
    json::object ret;
    ret["float_var_"]  = to_json(instance.float_var_);
    ret["double_var_"] = to_json(instance.double_var_);
    ret["bool_var_"]   = to_json(instance.bool_var_);
    ret["string_var_"] = to_json(instance.string_var_);

    return ret;
}
template<>
void meta::serializer::from_json(const json &json_context, serializer_test_2 &instance) {
    from_json(json_context["float_var_"], instance.float_var_);
    from_json(json_context["double_var_"], instance.double_var_);
    from_json(json_context["bool_var_"], instance.bool_var_);
    from_json(json_context["string_var_"], instance.string_var_);
}
template<>
json meta::serializer::to_json(serializer_test_3 &instance) {
    json::object ret;
    ret["serializer_test_1_var_"] = to_json(instance.serializer_test_1_var_);
    ret["serializer_test_2_var_"] = to_json(instance.serializer_test_2_var_);

    return ret;
}
template<>
void meta::serializer::from_json(const json &json_context, serializer_test_3 &instance) {
    from_json(json_context["serializer_test_1_var_"], instance.serializer_test_1_var_);
    from_json(json_context["serializer_test_2_var_"], instance.serializer_test_2_var_);
}