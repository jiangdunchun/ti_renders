#ifndef __REFLECTION_H__
#define __REFLECTION_H__

#include <json11/json11.hpp>

#include <functional>

#define REFLECTION_TYPE(t_name) \
    class type_##t_name##_operator; \

#define REFLECTION_BODY(t_name) \
    friend class type_##t_name##_operator; \
    friend class tigine::serializer;

namespace tigine {
    using json = json11::Json;

    class serializer {
    public:
        template<typename T>
        static json to_json(const T& instance);
        template<typename T>
        static bool from_json(const json& json_context, T& instance);
    };

    template<>
    json serializer::to_json(const int& instance);
    template<>
    bool serializer::from_json(const json& json_context, int& instance);
    template<>
    json serializer::to_json(const double& instance);
    template<>
    bool serializer::from_json(const json& json_context, double& instance);
    template<>
    json serializer::to_json(const bool& instance);
    template<>
    bool serializer::from_json(const json& json_context, bool& instance);
    template<>
    json serializer::to_json(const std::string& instance);
    template<>
    bool serializer::from_json(const json& json_context, std::string& instance);
}

#include <map>
#include <string>

typedef void* (*create_object_func)(void);

namespace tigine {
    class propety_meta;
    //class type_meta {
    //public:
    //    static type_meta get_by_name(const std::string&& t_name);
    //    void* create();
    //    unsigned int get_properties(propety_meta*& properties);
    //};

    //class propety_meta {
    //public:
    //    type_meta get_type_meta();
    //    void* get_value(void* instance);
    //    void set_value(void* instance, void* value);
    //    std::string get_property_name();
    //    std::string get_property_type_name();
    //};

    //class reflection {
    //private:
    //    static std::map<std::string, create_object_func> m_class_map;

    //public:
    //    static void* create_object(std::string class_name);
    //    static void regist_class(std::string class_name, create_object_func constructor);
    //};
}

namespace tigine {
    class variable_meta {
    public:
        variable_meta() = default;

        template<typename C, typename T>
        variable_meta(std::string name, T C::* var) : m_name(name) {
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

        const std::vector<variable_meta>& variables() const {
            return m_variables;
        }

        variable_meta get_varible(std::string v_name) {
            for (auto& v : m_variables)
                if (v.name() == v_name) return v;
            return variable_meta();
        }

        template<typename C, typename T>
        bool add_variable(std::string v_name, T C::* var) {
            for (auto& v : m_variables)
                if (v.name() == v_name) return false;

            m_variables.push_back(variable_meta(v_name, var));
            return true;
        }

    private:
        std::string m_name;
        std::vector<variable_meta> m_variables;
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
