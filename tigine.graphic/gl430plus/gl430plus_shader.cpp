#include "gl430plus_shader.h"

namespace tigine {
	inline GLuint map_shader_type(shader_type type) {
		switch (type) {
		case shader_type::vertex:
			return GL_VERTEX_SHADER;
			break;
		case shader_type::fragment:
			return GL_FRAGMENT_SHADER;
			break;
		case shader_type::compute:
			return GL_COMPUTE_SHADER;
			break;
		default:
			return 0;
			break;
		}
	}

	gl430plus_shader::gl430plus_shader(shader_type type) : m_type(type) {
		GLuint s_type = map_shader_type(type);
		// @TODO: check shader type
		m_id = glCreateShader(s_type);
	}

	gl430plus_shader::~gl430plus_shader()  {
		glDeleteShader(m_id);
	}

	void gl430plus_shader::compile_shader(const char* src_code) {
		glShaderSource(m_id, 1, &src_code, NULL);
		glCompileShader(m_id);
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &m_success);
		GLchar info_log[1024];
		if (!m_success) glGetShaderInfoLog(m_id, 1024, NULL, info_log);
		m_report = info_log;
	}
}