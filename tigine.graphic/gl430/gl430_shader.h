#ifndef TIGINE_GRAPHIC_GL430_GL430_SHADER_H_
#define TIGINE_GRAPHIC_GL430_GL430_SHADER_H_

#include <string>

#include "gl430/gl430_common.h"

namespace tigine {
namespace graphic {
enum class ShaderKind {
    Undefined,
    Vertex,
    Fragment,
    Compute,
};

struct ShaderDescriptor {
    ShaderKind kind = ShaderKind::Undefined;
    const char* code = nullptr;
};

class GL430Shader {
public:
    GL430Shader(const ShaderDescriptor& desc);
    ~GL430Shader();
    DISALLOW_COPY_AND_ASSIGN(GL430Shader);

    bool hasError() const;
    std::string getReport() const;
    GLuint id() const {
        return id_;
    }

private:
    GLuint id_ = 0;
};
} // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_GL430_GL430_SHADER_H_
