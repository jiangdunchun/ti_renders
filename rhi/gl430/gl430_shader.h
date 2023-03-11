#ifndef TIGINE_RHI_GL430_GL430_SHADER_H_
#define TIGINE_RHI_GL430_GL430_SHADER_H_

#include "gl430/gl430_common.h"
#include "interface/i_shader.h"

namespace tigine { namespace rhi {
class GL430Shader : public IShader {
public:
    GL430Shader(const ShaderDesc &desc);
    ~GL430Shader();

    bool        hasError() const;
    std::string getReport() const;
    GLuint      getID() const { return id_; }

private:
    GLuint id_ = 0;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_GL430_GL430_SHADER_H_
