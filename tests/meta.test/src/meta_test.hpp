#ifndef META_TEST_SERIALIZER_TEST_HPP_
#define META_TEST_SERIALIZER_TEST_HPP_

#include <meta.h>

#include <string>

CLASS() MetaTest1 {
public:
    char         char_var = 0;
    int          int_var = 0;
    unsigned int unsigned_int_var = 0;

    MetaTest1(char char_val, int int_val, unsigned int unsigned_int_val) {
        char_var         = char_val;
        int_var          = int_val;
        unsigned_int_var = unsigned_int_val;
    }
    MetaTest1() {}
};

CLASS() MetaTest2 {
public:
    float       float_var = 0;
    double      double_var = 0;
    bool        bool_var = false;
    std::string string_var = "";

    MetaTest2(float float_val, double double_val, bool bool_val, std::string string_val) {
        float_var  = float_val;
        double_var = double_val;
        bool_var   = bool_val;
        string_var = string_val;
    }
    MetaTest2() {}
};

CLASS(WHITE_LIST) MetaTest3 {
public:
    char char_var = 0;
    PROPERTY()
    MetaTest1 test_1_var;
    PROPERTY()
    MetaTest2 test_2_var;

    MetaTest3(MetaTest1 test_1_val, MetaTest2 test_2_val) {
        test_1_var = test_1_val;
        test_2_var = test_2_val;
    }
    MetaTest3() {}

    void set(char val) { char_var = val; }
    FUNCTION()
    char get() { return char_var; }
    FUNCTION()
    void plusandset(char val) { char_var += val; }
};

#endif // !META_TEST_SERIALIZER_TEST_HPP_
