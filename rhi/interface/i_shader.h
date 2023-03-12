#ifndef TIGINE_RHI_INTERFACE_I_SHADER_H_
#define TIGINE_RHI_INTERFACE_I_SHADER_H_

#include <string>

#include "interface/i_common.h"

namespace tigine { namespace rhi {
enum class ShaderKind {
    Vertex,
    Fragment,
    Compute,
};

struct ShaderDesc {
    ShaderKind   kind;
    TUInt        code_size = 0;
    const TChar *code      = nullptr;
};

class IShader : public NonCopyable {
public:
    virtual bool        hasError() const  = 0;
    virtual std::string getReport() const = 0;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_SHADER_H_
