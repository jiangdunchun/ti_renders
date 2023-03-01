#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_

#include "interface/i_shader.h"

#include "vulkan/vulkan_common.h"


namespace tigine { namespace graphic {
class VulkanShader : public IShader {
public:
    VulkanShader(VkDevice *vk_device, const ShaderDesc &desc);
    ~VulkanShader();

    bool        hasError() const override { return has_error_; }
    std::string getReport() const override { return "getReport() is not support in vulkan"; }

    VkShaderModule* getVKShaderModule() { return &vk_shader_; }

private:
    VkDevice *vk_device_;
    bool      has_error_ = false;

    VkShaderModule vk_shader_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_
