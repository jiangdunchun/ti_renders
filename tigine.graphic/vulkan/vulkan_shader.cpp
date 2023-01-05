#include "vulkan/vulkan_shader.h"

namespace tigine { namespace graphic {
VulkanShader::VulkanShader(VkDevice *vk_device, const ShaderDescriptor &desc) : vk_device_(vk_device) {
    VkShaderModuleCreateInfo create_info {};
    create_info.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.pCode    = reinterpret_cast<const uint32_t *>(desc.code);
    create_info.codeSize = desc.code_size;
    if (vkCreateShaderModule(*vk_device_, &create_info, nullptr, &vk_shader_) != VK_SUCCESS) has_error_ = true;
}

VulkanShader::~VulkanShader() { 
    vkDestroyShaderModule(*vk_device_, vk_shader_, nullptr);
}
}} // namespace tigine::graphic