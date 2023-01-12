#ifndef META_SERIALIZER_H_
#define META_SERIALIZER_H_

#include <string>

#include "json11.hpp"

using json = json11::Json;

namespace meta {
template<typename...>
inline constexpr bool always_false = false;

class serializer {
public:
    template<typename T>
    static json to_json_ptr(T *instance) {
        if (!instance) return json();
        return serializer::to_json(*instance);
    }

    template<typename T>
    static void from_json_ptr(const json &json_context, T *&instance) {
        if (!instance) return;
        serializer::from_json(json_context, *instance);
    }

    template<typename T>
    static json to_json(T &instance) {
        if constexpr (std::is_pointer<T>::value) {
            return to_json_ptr((T)instance);
        } else {
            static_assert(always_false<T>, "serializer::to_json<T> has not been implemented yet!");
            return json();
        }
    }

    template<typename T>
    static void from_json(const json &json_context, T &instance) {
        if constexpr (std::is_pointer<T>::value) {
            from_json_ptr(json_context, (T)instance);
        } else {
            static_assert(always_false<T>, "serializer::from_json<T> has not been implemented yet!");
        }
    }
};

template<>
json serializer::to_json(char &instance);
template<>
void serializer::from_json(const json &json_context, char &instance);
template<>
json serializer::to_json(int &instance);
template<>
void serializer::from_json(const json &json_context, int &instance);
template<>
json serializer::to_json(unsigned int &instance);
template<>
void serializer::from_json(const json &json_context, unsigned int &instance);
template<>
json serializer::to_json(float &instance);
template<>
void serializer::from_json(const json &json_context, float &instance);
template<>
json serializer::to_json(double &instance);
template<>
void serializer::from_json(const json &json_context, double &instance);
template<>
json serializer::to_json(bool &instance);
template<>
void serializer::from_json(const json &json_context, bool &instance);
template<>
json serializer::to_json(std::string &instance);
template<>
void serializer::from_json(const json &json_context, std::string &instance);
} // namespace meta

#endif // !META_SERIALIZER_H_
