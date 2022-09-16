#include "gl430/gl430_shader_program.h"

namespace tigine {
namespace graphic {
GL430plusShaderProgram::GL430plusShaderProgram(const ShaderProgramDescriptor& desc) {
	id_ = glCreateProgram();
	if (desc.vertex_shader) glAttachShader(id_, desc.vertex_shader->id());
	if (desc.fragment_shader) glAttachShader(id_, desc.fragment_shader->id());
	if (desc.compute_shader) glAttachShader(id_, desc.compute_shader->id());

	glLinkProgram(id_);

	GLint uniform_count = 0;
	glGetProgramiv(id_, GL_ACTIVE_UNIFORMS, &uniform_count);
	GLint max_name_len = 0;
	glGetProgramiv(id_, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_len);

	char* uniform_name = new char[max_name_len];
	GLsizei name_len = 0;
	GLint uniform_location = 0;
	GLint uniform_type = 0;
	for (GLuint i = 0; i < uniform_count; ++i) {
		glGetActiveUniformName(id_, i, max_name_len, &name_len, uniform_name);
		std::string name = uniform_name;
		GLint uniform_location = glGetUniformLocation(id_, name.c_str());
		glGetActiveUniformsiv(id_, 1, &i, GL_UNIFORM_TYPE, &uniform_type);
		uniforms_[name] = { uniform_location, uniform_type };
	}
	delete[] uniform_name;
}

GL430plusShaderProgram::~GL430plusShaderProgram() {
	glDeleteProgram(id_);
}

bool GL430plusShaderProgram::hasError() const {
	GLint success = 0;
	glGetProgramiv(id_, GL_LINK_STATUS, &success);
	return !success;
}

std::string GL430plusShaderProgram::getReport() const {
	GLint info_len = 0;
	glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &info_len);
	GLchar* info_log = new GLchar[info_len];
	glGetProgramInfoLog(id_, info_len, NULL, info_log);
	std::string report = info_log;
	delete[] info_log;
	return report;
}
} // namespace tigine::graphic
} // namspace tigine