#ifndef __GL430PLUS_SHADER_H__
#define __GL430PLUS_SHADER_H__

#include <string>

namespace tigine {
    enum class shader_type {
        undefined,    
        vertex,
        fragment,
        compute,
    };

	struct shader_descriptor {
        shader_type type = shader_type::undefined;
        const char* source = nullptr;
        std::size_t source_size = 0;
        vertex_attributes vertex;

	};

	class gl430plus_shader {
    private:
        shader_type m_type;

    protected:
        gl430plus_shader(const shader_type type) : m_type(type) {}

    public:
        virtual bool has_error() const = 0;
        virtual std::string get_report() const = 0;

	};
}

#endif // !__GL430PLUS_SHADER_H__
