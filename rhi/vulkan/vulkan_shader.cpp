#include "vulkan/vulkan_shader.h"

namespace tigine { namespace rhi {
VulkanShader::VulkanShader(const VulkanContextInfo &context, const ShaderDesc &desc) 
    : vk_device_(context.vk_device) {
    VkShaderModuleCreateInfo vk_module_info {};
    vk_module_info.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    vk_module_info.pCode    = reinterpret_cast<const uint32_t *>(desc.code);
    vk_module_info.codeSize = desc.code_size;
    if (vkCreateShaderModule(*context.vk_device, &vk_module_info, nullptr, &vk_shader_) != VK_SUCCESS) {
        has_error_ = true;
    }
}

VulkanShader::~VulkanShader() { 
    vkDestroyShaderModule(*vk_device_, vk_shader_, nullptr);
}
}} // namespace tigine::rhi