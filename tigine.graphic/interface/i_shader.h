#ifndef TIGINE_GRAPHIC_INTERFACE_I_SHADER_H_
#define TIGINE_GRAPHIC_INTERFACE_I_SHADER_H_

#include <string>

#include "interface/i_common.h"

namespace tigine { namespace graphic {
enum class ShaderKind {
    Undefined,
    Vertex,
    Fragment,
    Compute,
};

struct ShaderDesc {
    ShaderKind   kind      = ShaderKind::Undefined;
    TUInt        code_size = 0;
    const TChar *code      = nullptr;
};

class IShader : public NonCopyable {
public:
    virtual bool        hasError() const  = 0;
    virtual std::string getReport() const = 0;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_SHADER_H_
