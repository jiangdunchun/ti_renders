#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_

#include "vulkan/vulkan_common.h"
#include "interface/i_shader.h"

namespace tigine { namespace graphic {
class VulkanShader : public IShader {
public:
    VulkanShader(const ShaderDescriptor &desc);
    ~VulkanShader();

    bool        hasError() const;
    std::string getReport() const;
    GLuint      getID() const { return id_; }

private:
    GLuint id_ = 0;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_
