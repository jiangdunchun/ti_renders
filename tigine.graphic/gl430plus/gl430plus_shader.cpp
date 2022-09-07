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

	gl430plus_shader::gl430plus_shader(const shader_descriptor& desc) : m_type(desc.type) {
		GLuint s_type = map_shader_type(desc.type);
		// @todo: check type
		m_id = glCreateShader(s_type);
		glShaderSource(m_id, 1, &desc.source, NULL);
		glCompileShader(m_id);
	}

	gl430plus_shader::~gl430plus_shader()  {
		glDeleteShader(m_id);
	}

	bool gl430plus_shader::has_error() const {
		GLint success = 0;
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
		return !success;
	}

	std::string gl430plus_shader::get_report() const {
		GLint info_len = 0;
		glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &info_len);
		GLchar* info_log = new GLchar[info_len];
		glGetShaderInfoLog(m_id, info_len, NULL, info_log);
		std::string report = info_log;
		delete[] info_log;
		return report;
	}
}