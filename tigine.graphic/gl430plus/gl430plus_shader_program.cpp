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

	bool gl430plus_shader_program::has_error() {
		glGetProgramiv(m_id, GL_LINK_STATUS, &m_log_len);
		return m_log_len != 0;
	}

	std::string gl430plus_shader_program::get_report() const {
		GLchar* info_log = new GLchar[m_log_len];
		glGetProgramInfoLog(m_id, m_log_len, NULL, info_log);
		std::string report = info_log;
		delete[] info_log;
		return report;
	}
}