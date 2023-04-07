#ifndef TIGINE_RHI_INTERFACE_I_SHADER_PROGRAM_H_
#define TIGINE_RHI_INTERFACE_I_SHADER_PROGRAM_H_

#include "interface/i_common.h"
#include "interface/i_shader.h"

namespace tigine { namespace rhi {
struct ShaderProgramDesc {
    IShader *vertex_shader   = nullptr;
    IShader *fragment_shader = nullptr;
    IShader *compute_shader  = nullptr;
};

class IShaderProgram : public NonCopyable {
public:
    virtual ~IShaderProgram() = default;

    virtual bool        hasError() const  = 0;
    virtual std::string getReport() const = 0;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_SHADER_H_
