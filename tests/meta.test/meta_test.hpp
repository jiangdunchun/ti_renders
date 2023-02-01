#ifndef META_TEST_META_TEST_HPP_
#define META_TEST_META_TEST_HPP_

#define CLASS(...) class __attribute__((annotate("META;" #__VA_ARGS__)))
#define PROPERTY(...) __attribute__((annotate("META;" #__VA_ARGS__)))
#define FUNCTION(...) __attribute__((annotate("META;" #__VA_ARGS__)))

#define META_REFLECTIBLE \
public:                  \
    static void makeReflectible();

namespace meta {
class Serializer;
}
#define MEATA_SERIALIZABLE friend class meta::Serializer;

#define META_REFLECTIBLE_AND_SERIALIZABLE \
    friend class meta::Serializer;        \
public:                                   \
    static void makeReflectible();

namespace MetaTest {
CLASS(WHITE_LIST) MetaTest1 {
    META_REFLECTIBLE_AND_SERIALIZABLE
public:
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
