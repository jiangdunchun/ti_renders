#ifndef META_TEST_REFLECTOR_TEST_HPP_
#define META_TEST_REFLECTOR_TEST_HPP_

#include <meta.h>

class ReflectorTest1 {
    META_REFLECTIBLE
public:
    char         char_var_;
    int          int_var_;
    unsigned int unsigned_int_var_;

    ReflectorTest1(char char_var, int int_var, unsigned int unsigned_int_var) {
        char_var_         = char_var;
        int_var_          = int_var;
        unsigned_int_var_ = unsigned_int_var;
    }
    ReflectorTest1() {}

    char plusCharVar(char v) { return char_var_ + v; }
    void plusIntVar(int v) { int_var_ += v; }
};





/* auto generated code */
/*start---------->*/
void ReflectorTest1::makeReflectible() {
    meta::Reflector::registType<ReflectorTest1>("ReflectorTest1")
        .addField("char_var_", &ReflectorTest1::char_var_)
        .addField("int_var_", &ReflectorTest1::int_var_)
        .addField("unsigned_int_var_", &ReflectorTest1::unsigned_int_var_)
        .addMethod("plusCharVar", &ReflectorTest1::plusCharVar)
        .addMethod("plusIntVar", &ReflectorTest1::plusIntVar);
}
/*<----------end*/

#endif // !META_TEST_REFLECTOR_TEST_HPP_
