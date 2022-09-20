#include "gl430/gl430_shader.h"

namespace tigine {
namespace graphic {
namespace {
GLuint mapShaderKind(ShaderKind kind) {
	switch (kind) {
	case ShaderKind::Vertex:
		return GL_VERTEX_SHADER;
		break;
	case ShaderKind::Fragment:
		return GL_FRAGMENT_SHADER;
		break;
	case ShaderKind::Compute:
		return GL_COMPUTE_SHADER;
		break;
	default:
		return 0;
		break;
	}
}
} // namespace

GL430Shader::GL430Shader(const ShaderDescriptor& desc) {
	// assert kind
	GLuint kind = mapShaderKind(desc.kind);
	id_ = glCreateShader(kind);
	glShaderSource(id_, 1, &desc.code, NULL);
	glCompileShader(id_);
}

GL430Shader::~GL430Shader() {
	glDeleteShader(id_);
}

bool GL430Shader::hasError() const {
	GLint success = 0;
	glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
	return !success;
}

std::string GL430Shader::getReport() const {
	GLint info_len = 0;
	glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &info_len);
	GLchar* info_log = new GLchar[info_len];
	glGetShaderInfoLog(id_, info_len, NULL, info_log);
	std::string report = info_log;
	delete[] info_log;
	return report;
}

}} // namespace tigine::graphic