#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_PROGRAM_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_PROGRAM_H_

#include <map>
#include <string>

#include "vulkan/vulkan_common.h"
#include "interface/i_shader_program.h"

namespace tigine { namespace graphic {
class VulkanShaderProgram : public IShaderProgram {
public:
    VulkanShaderProgram(const ShaderProgramDescriptor &desc);
    ~VulkanShaderProgram();

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

}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_
