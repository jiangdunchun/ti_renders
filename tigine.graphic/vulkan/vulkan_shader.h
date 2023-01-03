#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_

#include "vulkan/vulkan_common.h"
#include "interface/i_shader.h"

namespace tigine { namespace graphic {
class VulkanShader : public IShader {
public:
    VulkanShader(VkDevice *device, const ShaderDescriptor &desc);
    ~VulkanShader();

    bool            hasError() const override { return has_error_; }
    std::string     getReport() const override { return "getReport() is not support in vulkan"; }
    VkShaderModule* getVKShaderModule() { return &vk_shader_; }

private:
    VkDevice      *vk_device_;
    VkShaderModule vk_shader_;
    bool           has_error_ = false;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_
