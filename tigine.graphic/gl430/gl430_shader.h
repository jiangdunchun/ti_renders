#ifndef TIGINE_GRAPHIC_GL430_GL430_SHADER_H_
#define TIGINE_GRAPHIC_GL430_GL430_SHADER_H_

#include "gl430/gl430_common.h"
#include "interface/i_shader.h"

namespace tigine { namespace graphic {
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
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_GL430_GL430_SHADER_H_
