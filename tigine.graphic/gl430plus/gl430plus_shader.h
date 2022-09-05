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
	};

	class gl430plus_shader {
    private:
        GLuint m_id = 0;
        shader_type m_type;
        int m_success = 0;
        std::string m_report = "";

    public:
        gl430plus_shader(shader_type type);
        ~gl430plus_shader();
        void compile_shader(const char* src_code);
        bool has_error() const {
            return m_success;
        }
        std::string get_report() const {
            return m_report;
        }
	};
}

#endif // !__GL430PLUS_SHADER_H__
