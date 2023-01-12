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
    TypeMeta(const std::string &getName) : name_(getName) {}

    const std::string &getName() const { return name_; }
    const std::vector<FieldMeta> &getVariables() const { return variables_; }

    FieldMeta getVarible(std::string v_name) {
        for (auto &v : variables_)
            if (v.getName() == v_name) return v;
        return FieldMeta();
    }
    template<typename C, typename T>
    bool addVariable(std::string v_name, T C::*var) {
        for (auto &v : variables_)
            if (v.getName() == v_name) return false;

        variables_.push_back(FieldMeta(v_name, var));
        return true;
    }

private:
    std::string            name_;
    std::vector<FieldMeta> variables_;
};

template<typename T>
class TypeMetaBuilder {
public:
    TypeMetaBuilder(const std::string &getName) : m_t_meta(getName) {}

    ~TypeMetaBuilder() { Reflector::regist(m_t_meta); }

    template<typename V>
    TypeMetaBuilder &add_variable(const std::string &getName, V T::*var) {
        m_t_meta.add_variable(getName, var);
        return *this;
    }

private:
    TypeMeta m_t_meta;
};

class Reflector {
private:
    static std::map<std::string, TypeMeta> sm_types;

public:
    template<typename T>
    static TypeMetaBuilder<T> regist_class(const std::string &getName) {
        return TypeMetaBuilder<T>(getName);
    }

    static bool regist(TypeMeta t_meta) {
        auto iter = sm_types.find(t_meta.getName());
        if (iter != sm_types.end()) return false;

        sm_types[t_meta.getName()] = t_meta;
        return true;
    }

    static void clear() { sm_types.clear(); }

    static TypeMeta get_type(const std::string &t_name) {
        auto iter = sm_types.find(t_name);
        if (iter == sm_types.end()) return TypeMeta();

        return iter->second;
    }
};
} // namespace meta

#endif // !META_REFLECTOR_H_
