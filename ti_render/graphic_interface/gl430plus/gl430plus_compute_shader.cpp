#include "gl430plus_compute_shader.h"

using namespace std;
using namespace glm;

namespace ti_render {
    inline void check_compile_errors(
        GLuint id,
        const string& type,
        const string& code) {
        GLint success;
        GLchar info_log[1024];

        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(id, 1024, NULL, info_log);
            logger_management::log(log_tag::LOG_ERROR,
                "graphic_interface::gl430plus_compute_shader:compile error\n"
                + type + "------------>\n"
                + code + +"\n"
                + "=====================\n"
                + "info: " + info_log + "\n");
        }
    }

    inline void check_link_errors(
        GLuint id, 
        const string& code) {
        GLint success;
        GLchar info_log[1024];

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id, 1024, NULL, info_log);
            logger_management::log(log_tag::LOG_ERROR,
                "graphic_interface::gl430plus_compute_shader:link error\COMPUTE------------>\n"
                + code + "\n"
                + "=====================\n"
                + "info: " + info_log + "\n");
        }
    }

	unsigned int gl430plus_compute_shader::sm_texture_index = 0;

    gl430plus_compute_shader::gl430plus_compute_shader(const string& code) {
        unsigned int c_id;
        const char* c_code = code.c_str();
        c_id = glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(c_id, 1, &c_code, NULL);
        glCompileShader(c_id);
        check_compile_errors(c_id, "COMPUTE", code);

        m_id = glCreateProgram();
        glAttachShader(m_id, c_id);
        glLinkProgram(m_id);
        check_link_errors(
            m_id,
            code);
        glDeleteShader(c_id);
    }

	gl430plus_compute_shader::~gl430plus_compute_shader() {
        glDeleteProgram(m_id);
	}

    void gl430plus_compute_shader::use(void) const {
        glUseProgram(m_id);
        gl430plus_compute_shader::sm_texture_index = 0;
    }

    void gl430plus_compute_shader::bind_texture(
        unsigned int attachment,
        gl430plus_texture_2d* texture,
        int access,
        unsigned int mipmap_layer) {
        glBindImageTexture(
            attachment, 
            texture->m_id, 
            mipmap_layer, 
            GL_FALSE, 
            0,
            map_access_type(access),
            map_color_internal_format(texture->get_color_format()));
    }

    void gl430plus_compute_shader::compute(unsigned int num_x, unsigned int num_y, unsigned int num_z) {
        glDispatchCompute(num_x, num_y, num_z);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    }

    void gl430plus_compute_shader::set_bool(const string& name, const bool value) const {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
    }

    void gl430plus_compute_shader::set_int(const string& name, const int value) const {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void gl430plus_compute_shader::set_float(const string& name, const float value) const {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void gl430plus_compute_shader::set_vec2(const string& name, const vec2& value) const {
        glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void gl430plus_compute_shader::set_vec3(const string& name, const vec3& value) const {
        glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void gl430plus_compute_shader::set_vec4(const string& name, const vec4& value) const {
        glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void gl430plus_compute_shader::set_mat2(const string& name, const mat2& value) const {
        glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void gl430plus_compute_shader::set_mat3(const string& name, const mat3& value) const {
        glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void gl430plus_compute_shader::set_mat4(const string& name, const mat4& value) const {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void gl430plus_compute_shader::set_texture_2d(const string& name, const gl430plus_texture_2d& value) const {
        glActiveTexture(GL_TEXTURE0 + sm_texture_index);
        set_int(name.c_str(), sm_texture_index);
        glBindTexture(GL_TEXTURE_2D, value.m_id);
        sm_texture_index++;
    }

    void gl430plus_compute_shader::set_texture_cube(const string& name, const gl430plus_texture_cube& value) const {
        glActiveTexture(GL_TEXTURE0 + sm_texture_index);
        set_int(name.c_str(), sm_texture_index);
        glBindTexture(GL_TEXTURE_CUBE_MAP, value.m_id);
        sm_texture_index++;
    }
}


