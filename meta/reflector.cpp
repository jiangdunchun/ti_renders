#include "reflector.h"

namespace meta {
std::map<std::string, TypeMeta> Reflector::types_ = {};

bool Reflector::regist(TypeMeta type) {
    auto iter = types_.find(type.getName());
    if (iter != types_.end()) return false;

    types_[type.getName()] = type;
    return true;
}

void Reflector::clear() { types_.clear(); }

TypeMeta Reflector::getType(const std::string &name) {
    auto iter = types_.find(name);
    if (iter == types_.end()) return TypeMeta();

    return iter->second;
}
} // namespace meta