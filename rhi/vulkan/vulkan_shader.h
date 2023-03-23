#ifndef TIGINE_RHI_VULKAN_VULKAN_SHADER_H_
#define TIGINE_RHI_VULKAN_VULKAN_SHADER_H_

#include "interface/i_shader.h"

#include <string>

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanShader : public IShader {
public:
    VulkanShader(const VulkanContextInfo &context, const ShaderDesc &desc);
    ~VulkanShader();

    bool        hasError() const override { return has_error_; }
    std::string getReport() const override { return "getReport() is not support in vulkan"; }

    VkShaderModule* getVKShaderModule() { return &vk_shader_; }

private:
    VkDevice *vk_device_;
    bool      has_error_ = false;

    VkShaderModule vk_shader_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_SHADER_H_
