#include "serializer.h"

#include <assert.h>

namespace meta {
template<>
json serializer::to_json(char& instance) {
    return json(instance);
}

template<>
void serializer::from_json(const json& json_context, char& instance) {
    assert(json_context.is_number());
    instance = static_cast<char>(json_context.number_value());
}

template<>
json serializer::to_json(int& instance) {
    return json(instance);
}

template<>
void serializer::from_json(const json& json_context, int& instance) {
    assert(json_context.is_number());
    instance = static_cast<int>(json_context.number_value());
}

template<>
json serializer::to_json(unsigned int& instance) {
    return json(static_cast<int>(instance));
}

template<>
void serializer::from_json(const json& json_context, unsigned int& instance) {
    assert(json_context.is_number());
    instance = static_cast<unsigned int>(json_context.number_value());
}

template<>
json serializer::to_json(float& instance) {
    return json(instance);
}

template<>
void serializer::from_json(const json& json_context, float& instance) {
    assert(json_context.is_number());
    instance = static_cast<float>(json_context.number_value());
}

template<>
json serializer::to_json(double& instance) {
    return json(instance);
}

template<>
void serializer::from_json(const json& json_context, double& instance) {
    assert(json_context.is_number());
    instance = static_cast<double>(json_context.number_value());
}

template<>
json serializer::to_json(bool& instance) {
    return json(instance);
}

template<>
void serializer::from_json(const json& json_context, bool& instance) {
    assert(json_context.is_bool());
    instance = json_context.bool_value();
}

template<>
json serializer::to_json(std::string& instance) {
    return json(instance);
}

template<>
void serializer::from_json(const json& json_context, std::string& instance) {
    assert(json_context.is_string());
    instance = json_context.string_value();
}
} // namespace meta