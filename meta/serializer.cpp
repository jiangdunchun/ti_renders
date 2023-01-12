#include "serializer.h"

#include <assert.h>

namespace meta {
template<>
json Serializer::toJson(char& instance) {
    return json(instance);
}

template<>
void Serializer::fromJson(const json& json_context, char& instance) {
    assert(json_context.is_number());
    instance = static_cast<char>(json_context.number_value());
}

template<>
json Serializer::toJson(int& instance) {
    return json(instance);
}

template<>
void Serializer::fromJson(const json& json_context, int& instance) {
    assert(json_context.is_number());
    instance = static_cast<int>(json_context.number_value());
}

template<>
json Serializer::toJson(unsigned int& instance) {
    return json(static_cast<int>(instance));
}

template<>
void Serializer::fromJson(const json& json_context, unsigned int& instance) {
    assert(json_context.is_number());
    instance = static_cast<unsigned int>(json_context.number_value());
}

template<>
json Serializer::toJson(float& instance) {
    return json(instance);
}

template<>
void Serializer::fromJson(const json& json_context, float& instance) {
    assert(json_context.is_number());
    instance = static_cast<float>(json_context.number_value());
}

template<>
json Serializer::toJson(double& instance) {
    return json(instance);
}

template<>
void Serializer::fromJson(const json& json_context, double& instance) {
    assert(json_context.is_number());
    instance = static_cast<double>(json_context.number_value());
}

template<>
json Serializer::toJson(bool& instance) {
    return json(instance);
}

template<>
void Serializer::fromJson(const json& json_context, bool& instance) {
    assert(json_context.is_bool());
    instance = json_context.bool_value();
}

template<>
json Serializer::toJson(std::string& instance) {
    return json(instance);
}

template<>
void Serializer::fromJson(const json& json_context, std::string& instance) {
    assert(json_context.is_string());
    instance = json_context.string_value();
}
} // namespace meta