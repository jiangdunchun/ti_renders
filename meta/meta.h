#ifndef META_META_H_
#define META_META_H_

#include <serializer.h>
#include <reflector.h>

#define META_REFLECTIBLE \
public: \
    static void makeReflectible(); \

#define MEATA_SERIALIZABLE \
friend class meta::Serializer; \

#define META_REFLECTIBLE_AND_SERIALIZABLE \
friend class meta::Serializer; \
public: \
    static void makeReflectible(); \

#ifdef __META_PARSER__
#define META_FIELD(...) __attribute__((annotate("META_FIELD;" #__VA_ARGS__)))
#else
#define META_FIELD(...)
#endif // __META_PASER__


#endif // !META_META_H_