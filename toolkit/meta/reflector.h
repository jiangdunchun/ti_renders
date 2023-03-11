#ifndef META_REFLECTOR_H_
#define META_REFLECTOR_H_

#include <string>
#include <functional>
#include <map>
#include <vector>
#include <any>

namespace meta {
class FieldMeta {
public:
    FieldMeta() = default;
    template<typename T, typename F>
    explicit FieldMeta(F T::*field, const std::string &name = "") : name_(name) {
        get_func_ = [field](void *obj) -> void * { return &(static_cast<T *>(obj)->*field); };
        set_func_ = [field](void *obj, void *val) {
            T *self    = static_cast<T *>(obj);
            self->*field = *(static_cast<F *>(val));
        };
    }

    const std::string &getName() const { return name_; }
    template<typename F, typename T>
    F get(T &instance) const {
        return *(static_cast<F *>(get_func_(&instance)));
    }
    template<typename T, typename F>
    void set(T &instance, F &&val) const {
        set_func_(&instance, &val);
    }

private:
    std::string                         name_;
    std::function<void *(void *)>       get_func_ = nullptr;
    std::function<void(void *, void *)> set_func_ = nullptr;
};

class MethodMeta {
public:
    MethodMeta() = default;
    template<typename T, typename R, typename... Args>
    explicit MethodMeta(R (T::*method)(Args...), const std::string &name = "") : name_(name) {
        func_ = [this, method](std::any obj_args) -> std::any {
            using tuple_t = std::tuple<T &, Args...>;
            auto *tp_ptr = std::any_cast<tuple_t *>(obj_args);
            return std::apply(method, *tp_ptr);
        };
    }
    template<typename T, typename... Args>
    explicit MethodMeta(void (T::*method)(Args...), const std::string &name = "") : name_(name) {
        func_ = [this, method](std::any obj_args) -> std::any {
            using tuple_t = std::tuple<T &, Args...>;
            auto *tp_ptr  = std::any_cast<tuple_t *>(obj_args);
            std::apply(method, *tp_ptr);
            return std::any {};
        };
    }
    template<typename T, typename R, typename... Args>
    explicit MethodMeta(R (T::*method)(Args...) const, const std::string &name = "") : name_(name) {
        func_ = [this, method](std::any obj_args) -> std::any {
            using tuple_t = std::tuple<const T &, Args...>;
            auto *tp_ptr = std::any_cast<tuple_t *>(obj_args);
            return std::apply(method, *tp_ptr);
        };
        is_const_ = true;
    }
    template<typename T, typename... Args>
    explicit MethodMeta(void (T::*method)(Args...) const, const std::string &name = "") : name_(name) {
        func_ = [this, method](std::any obj_args) -> std::any {
            using tuple_t = std::tuple<const T &, Args...>;
            auto *tp_ptr  = std::any_cast<tuple_t *>(obj_args);
            std::apply(method, *tp_ptr);
            return std::any {};
        };
        is_const_ = true;
    }

    const std::string &getName() const { return name_; }
    bool isConst() const { return is_const_; }
    template<typename R, typename T, typename... Args>
    R invoke(T &instance, Args &&...args) {
        if (is_const_) {
            auto tp = std::make_tuple(std::reference_wrapper<const T>(instance), args...);
            return std::any_cast<R>(func_(&tp));
        }
        auto tp = std::make_tuple(std::reference_wrapper<T>(instance), args...);
        return std::any_cast<R>(func_(&tp));
    }
    template<typename T, typename... Args>
    void invoke(T &instance, Args &&...args) {
        if (is_const_) {
            auto tp = std::make_tuple(std::reference_wrapper<const T>(instance), args...);
            func_(&tp);
        }
        auto tp = std::make_tuple(std::reference_wrapper<T>(instance), args...);
        func_(&tp);
    }

private:
    friend class RawTypeDescriptorBuilder;

    std::string                       name_;
    bool                              is_const_ = false;
    std::function<std::any(std::any)> func_ = nullptr;
};

class TypeMeta {
public:
    TypeMeta() = default;
    TypeMeta(const std::string &name) : name_(name) {}

    const std::string &getName() const { return name_; }
    const std::vector<FieldMeta> &getFields() const { return fields_; }
    FieldMeta getField(const std::string &name) {
        for (auto &f : fields_)
            if (f.getName() == name) return f;
        return FieldMeta();
    }
    template<typename T, typename F>
    bool addField(const std::string &name, F T::*field) {
        for (auto &f : fields_)
            if (f.getName() == name) return false;

        fields_.push_back(FieldMeta(field, name));
        return true;
    }
    const std::vector<MethodMeta> &getMethods() const { return methods_; }
    MethodMeta getMethod(const std::string &name) {
        for (auto &m : methods_)
            if (m.getName() == name) return m;
        return MethodMeta();
    }
    template<typename M>
    bool addMethod(const std::string &name, M method) {
        for (auto &m : methods_)
            if (m.getName() == name) return false;

        methods_.push_back(MethodMeta(method, name));
        return true;
    }

private:
    std::string             name_;
    std::vector<FieldMeta>  fields_;
    std::vector<MethodMeta> methods_;
};

template<typename T>
class TypeMetaBuilder {
public:
    TypeMetaBuilder(const std::string &name) : type_(name) {}
    ~TypeMetaBuilder();

    template<typename F>
    TypeMetaBuilder &addField(const std::string &name, F T::*field) {
        type_.addField(name, field);
        return *this;
    }
    template<typename M>
    TypeMetaBuilder &addMethod(const std::string &name, M method) {
        type_.addMethod(name, method);
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

    static void registAll();
    static bool regist(TypeMeta type);
    static void clear();
    static TypeMeta getType(const std::string &name);
};

template<typename T>
TypeMetaBuilder<T>::~TypeMetaBuilder() { Reflector::regist(type_); }
} // namespace meta

#endif // !META_REFLECTOR_H_
