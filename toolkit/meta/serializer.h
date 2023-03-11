#ifndef META_SERIALIZER_H_
#define META_SERIALIZER_H_

#include <string>

#include "json11.hpp"

using json = json11::Json;

namespace meta {
template<typename...>
inline constexpr bool always_false = false;

class Serializer {
public:
    template<typename T>
    static json toJsonPtr(T *instance) {
        if (!instance) return json();
        return Serializer::toJson(*instance);
    }

    template<typename T>
    static void fromJsonPtr(const json &json_context, T *&instance) {
        if (!instance) return;
        Serializer::fromJson(json_context, *instance);
    }

    template<typename T>
    static json toJson(T &instance) {
        if constexpr (std::is_pointer<T>::value) {
            return toJsonPtr((T)instance);
        } else {
            static_assert(always_false<T>, "Serializer::toJson<T> has not been implemented yet!");
            return json();
        }
    }

    template<typename T>
    static void fromJson(const json &json_context, T &instance) {
        if constexpr (std::is_pointer<T>::value) {
            fromJsonPtr(json_context, (T)instance);
        } else {
            static_assert(always_false<T>, "Serializer::fromJson<T> has not been implemented yet!");
        }
    }
};

template<>
json Serializer::toJson(char &instance);
template<>
void Serializer::fromJson(const json &json_context, char &instance);
template<>
json Serializer::toJson(int &instance);
template<>
void Serializer::fromJson(const json &json_context, int &instance);
template<>
json Serializer::toJson(unsigned int &instance);
template<>
void Serializer::fromJson(const json &json_context, unsigned int &instance);
template<>
json Serializer::toJson(float &instance);
template<>
void Serializer::fromJson(const json &json_context, float &instance);
template<>
json Serializer::toJson(double &instance);
template<>
void Serializer::fromJson(const json &json_context, double &instance);
template<>
json Serializer::toJson(bool &instance);
template<>
void Serializer::fromJson(const json &json_context, bool &instance);
template<>
json Serializer::toJson(std::string &instance);
template<>
void Serializer::fromJson(const json &json_context, std::string &instance);
} // namespace meta

#endif // !META_SERIALIZER_H_
