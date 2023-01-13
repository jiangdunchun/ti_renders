#ifndef META_REFLECTOR_H_
#define META_REFLECTOR_H_

#include <string>
#include <functional>
#include <map>
#include <vector>

namespace meta {
class FieldMeta {
public:
    FieldMeta() = default;
    template<typename C, typename T>
    FieldMeta(std::string getName, T C::*var) : name_(getName) {
        get_func_ = [var](void *obj) -> void * { return &(static_cast<C *>(obj)->*var); };
        set_func_ = [var](void *obj, void *val) {
            C *self    = static_cast<C *>(obj);
            self->*var = *(static_cast<T *>(val));
        };
    }

    const std::string &getName() const { return name_; }
    template<typename T, typename C>
    T get(C &c) const {
        return *(static_cast<T *>(get_func_(&c)));
    }
    template<typename C, typename T>
    void set(C &c, T &&val) const {
        set_func_(&c, &val);
    }

private:
    std::string                         name_;
    std::function<void *(void *)>       get_func_ = nullptr;
    std::function<void(void *, void *)> set_func_ = nullptr;
};

class TypeMeta {
public:
    TypeMeta() = default;
    TypeMeta(const std::string &name) : name_(name) {}

    const std::string &getName() const { return name_; }
    const std::vector<FieldMeta> &getFields() const { return fields_; }
    FieldMeta getField(std::string v_name) {
        for (auto &v : fields_)
            if (v.getName() == v_name) return v;
        return FieldMeta();
    }
    template<typename C, typename T>
    bool addField(std::string v_name, T C::*var) {
        for (auto &v : fields_)
            if (v.getName() == v_name) return false;

        fields_.push_back(FieldMeta(v_name, var));
        return true;
    }

private:
    std::string            name_;
    std::vector<FieldMeta> fields_;
};

template<typename T>
class TypeMetaBuilder {
public:
    TypeMetaBuilder(const std::string &name) : type_(name) {}
    ~TypeMetaBuilder() { Reflector::regist(type_); }

    template<typename V>
    TypeMetaBuilder &addField(const std::string &name, V T::*var) {
        type_.addField(name, var);
        return *this;
    }

private:
    TypeMeta type_;
};

class Reflector {
private:
    static std::map<std::string, TypeMeta> types_;

public:
    template<typename T>
    static TypeMetaBuilder<T> registType(const std::string &name) {
        return TypeMetaBuilder<T>(name);
    }

    static bool regist(TypeMeta type);
    static void clear();
    static TypeMeta getType(const std::string &name);
};
} // namespace meta

#endif // !META_REFLECTOR_H_
