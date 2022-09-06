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
	};

	class gl430plus_shader {
    private:
        GLuint m_id = 0;
        GLuint m_log_len = 0;
        shader_type m_type;

    public:
        gl430plus_shader(shader_type type);
        ~gl430plus_shader();
        bool has_error() const;
        std::string get_report() const;
	};
}

#endif // !__GL430PLUS_SHADER_H__
