#ifndef TIGINE_GRAPHIC_GL430_GL430_SHADER_PROGRAM_H_
#define TIGINE_GRAPHIC_GL430_GL430_SHADER_PROGRAM_H_

#include <map>
#include <string>

#include "gl430/gl430_common.h"
#include "gl430/gl430_shader.h"

namespace tigine {
namespace graphic {
struct ShaderProgramDescriptor {
	GL430Shader* vertex_shader = nullptr;
	GL430Shader* fragment_shader = nullptr;
	GL430Shader* compute_shader = nullptr;
};

class GL430ShaderProgram {
public:
	GL430ShaderProgram(const ShaderProgramDescriptor& desc);
	~GL430ShaderProgram();
	DISALLOW_COPY_AND_ASSIGN(GL430ShaderProgram);

	bool hasError() const;
	std::string getReport() const;
	GLuint id() const {
		return id_;
	}

private:
	GLuint id_;
	struct Uniform {
		GLint location;
		GLint type;
	};
	std::map<std::string, Uniform> uniforms_;
};

} // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_GL430_GL430_SHADER_H_
