#include "gl430plus_shader_program.h"

namespace tigine {
	gl430plus_shader_program::gl430plus_shader_program(const shader_program_descriptor& desc) {
		m_id = glCreateProgram();
		if (desc.vertex_shader) glAttachShader(m_id, desc.vertex_shader->get_id());
		if (desc.fragment_shader) glAttachShader(m_id, desc.fragment_shader->get_id());
		if (desc.compute_shader) glAttachShader(m_id, desc.compute_shader->get_id());

		glLinkProgram(m_id);

		GLint uniform_count = 0;
		glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &uniform_count);
		GLint max_name_len = 0;
		glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_len);

		char* uniform_name = new char[max_name_len];
		GLsizei name_len = 0;
		GLuint index = 0;
		GLint type;
		for (GLuint i = 0; i < uniform_count; ++i) {
			glGetActiveUniformName(m_id, i, max_name_len, &name_len, uniform_name);
			std::string name = uniform_name;
			GLint location = glGetUniformLocation(m_id, name.c_str());
			index = i;
			glGetActiveUniformsiv(m_id, 1, &index, GL_UNIFORM_TYPE, &type);
			m_uniforms[name] = { location, type };
		}
		delete[] uniform_name;
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