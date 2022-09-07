#include "gl430plus_shader_program.h"

namespace tigine {
	gl430plus_shader_program::gl430plus_shader_program(const shader_program_descriptor& desc) {
		m_id = glCreateProgram();
		if (desc.vertex_shader) glAttachShader(m_id, desc.vertex_shader->get_id());
		if (desc.fragment_shader) glAttachShader(m_id, desc.fragment_shader->get_id());
		if (desc.compute_shader) glAttachShader(m_id, desc.compute_shader->get_id());

		glLinkProgram(m_id);
	}

	gl430plus_shader_program::~gl430plus_shader_program() {
		glDeleteProgram(m_id);
	}

	bool gl430plus_shader_program::has_error() const {
		GLint success = 0;
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		return !success;
	}

	std::string gl430plus_shader_program::get_report() const {
		GLint info_len = 0;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &info_len);
		GLchar* info_log = new GLchar[info_len];
		glGetProgramInfoLog(m_id, info_len, NULL, info_log);
		std::string report = info_log;
		delete[] info_log;
		return report;
	}
}