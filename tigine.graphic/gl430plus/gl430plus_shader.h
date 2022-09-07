#ifndef __GL430PLUS_SHADER_H__
#define __GL430PLUS_SHADER_H__

#include <string>
#include "gl430plus_common.h"

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
        shader_type m_type;

    public:
        gl430plus_shader(const shader_descriptor& desc);
        ~gl430plus_shader();
        bool has_error() const;
        std::string get_report() const;
        GLuint get_id() const {
            return m_id;
        }
	};
}

#endif // !__GL430PLUS_SHADER_H__
