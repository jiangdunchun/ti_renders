#ifndef META_META_H_
#define META_META_H_

#include <serializer.h>
#include <reflector.h>

#ifdef __META_PARSER__
#define CLASS(...) class __attribute__((annotate("META;" #__VA_ARGS__)))
#define PROPERTY(...) __attribute__((annotate("META;" #__VA_ARGS__)))
#define FUNCTION(...) __attribute__((annotate("META;" #__VA_ARGS__)))
#else
#define CLASS(...) class
#define PROPERTY(...)
#define FUNCTION(...)
#endif // __META_PASER__


#endif // !META_META_H_