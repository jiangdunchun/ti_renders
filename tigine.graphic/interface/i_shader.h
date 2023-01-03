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

struct ShaderDescriptor {
    ShaderKind   kind      = ShaderKind::Undefined;
    const TChar *code      = nullptr;
    TUInt        code_size = 0;;
};

class IShader : public NonCopyable {
public:
    virtual bool        hasError() const  = 0;
    virtual std::string getReport() const = 0;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_SHADER_H_
