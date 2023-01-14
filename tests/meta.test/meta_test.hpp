#ifndef META_TEST_META_TEST_HPP_
#define META_TEST_META_TEST_HPP_

#include <meta.h>

#define CLASS() class __attribute__((annotate("reflect-class")))
#define PROPERTY() __attribute__((annotate("reflect-property")))

namespace MetaTest {
CLASS() MetaTest1 {
public:
    PROPERTY()
    char         char_var_;
    int          int_var_;
    unsigned int unsigned_int_var_;

    MetaTest1(char char_var, int int_var, unsigned int unsigned_int_var) {
        char_var_         = char_var;
        int_var_          = int_var;
        unsigned_int_var_ = unsigned_int_var;
    }
    MetaTest1() {}
};
} // namespace MetaTest
#endif // !META_TEST_META_TEST_HPP_
