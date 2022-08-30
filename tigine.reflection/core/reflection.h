#ifndef __REFLECTION_H__
#define __REFLECTION_H__

#include <json11/json11.hpp>
#include <map>
#include <string>
#include <functional>

namespace tigine {
    using json = json11::Json;
    class serializer {
    public:
        template<typename T>
        static json to_json_ptr(T* instance) {
            if (!instance) return json();
            return serializer::to_json(*instance);
        }

        template<typename T>
        static bool from_json_Ptr(const json& json_context, T*& instance) {
            if (!instance) return false;
            return serializer::from_json(json_context , *instance);
        }

        template<typename T>
        static json to_json(T& instance) {
            if constexpr (std::is_pointer<T>::value) {
                return to_json_ptr((T)instance);
            }
            else {
                static_assert(always_false<T>, "serializer::to_json<T> has not been implemented yet!");
                return json();
            }
        }

        template<typename T>
        static bool from_json(const json& json_context, T& instance) {
            if constexpr (std::is_pointer<T>::value) {
                return from_json_Ptr(json_context, (T)instance);
            }
            else {
                static_assert(always_false<T>, "serializer::to_json<T> has not been implemented yet!");
                return false;
            }
        }
    };

    template<>
    json serializer::to_json(int& instance) {
        return json(instance);
    }
    template<>
    bool serializer::from_json(const json& json_context, int& instance) {
        if (!json_context.is_number()) return false;
        instance = static_cast<int>(json_context.number_value());
        return true;
    }
    template<>
    json serializer::to_json(double& instance) {
        return json(instance);
    }
    template<>
    bool serializer::from_json(const json& json_context, double& instance) {
        if (!json_context.is_number()) return false;
        instance = static_cast<double>(json_context.number_value());
        return true;
    }
    template<>
    json serializer::to_json(bool& instance) {
        return json(instance);
    }
    template<>
    bool serializer::from_json(const json& json_context, bool& instance) {
        if (!json_context.is_bool()) return false;
        instance = json_context.bool_value();
        return true;
    }
    template<>
    json serializer::to_json(std::string& instance) {
        return json(instance);
    }
    template<>
    bool serializer::from_json(const json& json_context, std::string& instance) {
        if (!json_context.is_string()) return false;
        instance = json_context.string_value();
        return true;
    }
}

typedef void* (*create_object_func)(void);

namespace tigine {
    class field_meta {
    public:
        field_meta() = default;

        template<typename C, typename T>
        field_meta(std::string name, T C::* var) : m_name(name) {
            m_get_func = [var](void* obj) -> void* {
                return &(static_cast<C*>(obj)->*var);
            };
            m_set_func = [var](void* obj, void* val) {
                C* self = static_cast<C*>(obj);
                self->*var = *(static_cast<T*>(val));
            };
        }

        const std::string& name() const {
            return m_name;
        }

        template<typename T, typename C>
        T get(C& c) const {
            return *(static_cast<T*>(m_get_func(&c)));
        }

        template<typename C, typename T>
        void set(C& c, T&& val) const {
            m_set_func(&c, &val);
        }

    private:
        std::string m_name;
        std::function<void* (void*)> m_get_func = nullptr;
        std::function<void(void*, void*)> m_set_func = nullptr;
    };

    class type_meta {
    public:
        type_meta() = default;
        type_meta(const std::string& name) : m_name(name) { }

        const std::string& name() const {
            return m_name;
        }

        const std::vector<field_meta>& variables() const {
            return m_variables;
        }

        field_meta get_varible(std::string v_name) {
            for (auto& v : m_variables)
                if (v.name() == v_name) return v;
            return field_meta();
        }

        template<typename C, typename T>
        bool add_variable(std::string v_name, T C::* var) {
            for (auto& v : m_variables)
                if (v.name() == v_name) return false;

            m_variables.push_back(field_meta(v_name, var));
            return true;
        }

    private:
        std::string m_name;
        std::vector<field_meta> m_variables;
    };

    template <typename T>
    class type_meta_builder {
    public:
        type_meta_builder(const std::string& name) : m_t_meta(name) { }

        ~type_meta_builder() {
            reflection::regist(m_t_meta);
        }

        template <typename V>
        type_meta_builder& add_variable(const std::string& name, V T::* var) {
            m_t_meta.add_variable(name, var);
            return *this;
        }
    private:
        type_meta m_t_meta;
    };

    class reflection {
    private:
        static std::map<std::string, type_meta> sm_types;

    public:
        template <typename T>
        static type_meta_builder<T> regist_class(const std::string& name) {
            return type_meta_builder<T>(name);
        }

        static bool regist(type_meta t_meta) {
            auto iter = sm_types.find(t_meta.name());
            if (iter != sm_types.end()) return false;

            sm_types[t_meta.name()] = t_meta;
            return true;
        }

        static void clear() {
            sm_types.clear();
        }

        static type_meta get_type(const std::string& t_name) {
            auto iter = sm_types.find(t_name);
            if (iter == sm_types.end()) return type_meta();

            return iter->second;
        }
    };

    std::map<std::string, type_meta> reflection::sm_types = {};
}

#endif
