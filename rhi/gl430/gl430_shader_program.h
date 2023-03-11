#ifndef TIGINE_RHI_GL430_GL430_SHADER_PROGRAM_H_
#define TIGINE_RHI_GL430_GL430_SHADER_PROGRAM_H_

#include <map>
#include <string>

#include "gl430/gl430_common.h"
#include "interface/i_shader_program.h"

namespace tigine { namespace rhi {
class GL430ShaderProgram : public IShaderProgram {
public:
    GL430ShaderProgram(const ShaderProgramDesc &desc);
    ~GL430ShaderProgram();

    bool        hasError() const override;
    std::string getReport() const override;
    GLuint      getID() const { return id_; }

private:
    GLuint id_;
    struct Uniform {
        GLint location;
        GLint type;
    };
    std::map<std::string, Uniform> uniforms_;
};

}} // namespace tigine::rhi

#endif // !TIGINE_RHI_GL430_GL430_SHADER_H_
