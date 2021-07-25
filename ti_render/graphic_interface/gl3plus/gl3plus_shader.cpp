#include "gl3plus_shader.h"

namespace ti_render {
    inline void check_compile_errors(
        GLuint id,
        const std::string& type,
        const std::string& code) {
        GLint success;
        GLchar info_log[1024];

        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(id, 1024, NULL, info_log);
            logger_management::log(log_tag::LOG_ERROR,
                "graphic_interface::gl3plus_shader:compile error\n"
                + type + "------------>\n"
                + code + +"\n"
                + "=====================\n"
                + "info: " + info_log + "\n");
        }
    }

    inline void check_link_errors(
        GLuint id, 
        const std::string& v_code, 
        const std::string& f_code,
        const std::string& g_code = "") {
        GLint success;
        GLchar info_log[1024];

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id, 1024, NULL, info_log);
            logger_management::log(log_tag::LOG_ERROR,
                "graphic_interface::gl3plus_shader:link error\nVERTEX------------>\n"
                + v_code + "\n"
                + "GEOMETRY------------>\n"
                + g_code + "\n"
                + "FRAGMENT------------>\n"
                + f_code + "\n"
                + "=====================\n"
                + "info: " + info_log + "\n");
        }
    }

	unsigned int gl3plus_shader::sm_texture_index = 0;

    gl3plus_shader::gl3plus_shader(
        const std::string& vertex_code, 
        const std::string& fragment_code, 
        const std::string& geometry_code) {
        unsigned int v_id;
        const char* v_code = vertex_code.c_str();
        v_id = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(v_id, 1, &v_code, NULL);
        glCompileShader(v_id);
        check_compile_errors(v_id, "VERTEX", vertex_code);

        unsigned int f_id;
        const char* f_code = fragment_code.c_str();
        f_id = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(f_id, 1, &f_code, NULL);
        glCompileShader(f_id);
        check_compile_errors(f_id, "FRAGMENT", fragment_code);

        unsigned int g_id;
        if (geometry_code != "") {
            const char* g_code = geometry_code.c_str();
            g_id = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(g_id, 1, &g_code, NULL);
            glCompileShader(g_id);
            check_compile_errors(g_id, "GEOMETRY", geometry_code);
        }

        m_id = glCreateProgram();
        glAttachShader(m_id, v_id);
        glAttachShader(m_id, f_id);
        if (geometry_code != "") {
            glAttachShader(m_id, g_id);
        }
        glLinkProgram(m_id);
        check_link_errors(
            m_id,
            vertex_code,
            fragment_code,
            geometry_code);

        glDeleteShader(v_id);
        glDeleteShader(f_id);
        if (geometry_code != "") {
            glDeleteShader(g_id);
        }
    }

	gl3plus_shader::~gl3plus_shader() {
        glDeleteProgram(m_id);
	}

    void gl3plus_shader::use(void) const {
        glUseProgram(m_id);
        gl3plus_shader::sm_texture_index = 0;
    }

    void gl3plus_shader::set_bool(const std::string& name, const bool value) const {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
    }

    void gl3plus_shader::set_int(const std::string& name, const int value) const {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void gl3plus_shader::set_float(const std::string& name, const float value) const {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void gl3plus_shader::set_vec2(const std::string& name, const glm::vec2& value) const {
        glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void gl3plus_shader::set_vec3(const std::string& name, const glm::vec3& value) const {
        glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void gl3plus_shader::set_vec4(const std::string& name, const glm::vec4& value) const {
        glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void gl3plus_shader::set_mat2(const std::string& name, const glm::mat2& value) const {
        glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void gl3plus_shader::set_mat3(const std::string& name, const glm::mat3& value) const {
        glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void gl3plus_shader::set_mat4(const std::string& name, const glm::mat4& value) const {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void gl3plus_shader::set_texture_2d(const std::string& name, const gl3plus_texture_2d* value) const {
        glActiveTexture(GL_TEXTURE0 + sm_texture_index);
        set_int(name.c_str(), sm_texture_index);
        glBindTexture(GL_TEXTURE_2D, value->m_id);
        sm_texture_index++;
    }

    void gl3plus_shader::set_texture_cube(const std::string& name, const gl3plus_texture_cube* value) const {
        glActiveTexture(GL_TEXTURE0 + sm_texture_index);
        set_int(name.c_str(), sm_texture_index);
        glBindTexture(GL_TEXTURE_CUBE_MAP, value->m_id);
        sm_texture_index++;
    }
}


