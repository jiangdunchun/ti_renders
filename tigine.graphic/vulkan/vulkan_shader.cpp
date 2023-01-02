#include "vulkan/vulkan_shader.h"

namespace tigine { namespace graphic {
VulkanShader::VulkanShader(VkDevice *device, const ShaderDescriptor &desc) : device_(device) {
    VkShaderModuleCreateInfo create_info {};
    create_info.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.pCode    = reinterpret_cast<const uint32_t *>(desc.code);
    create_info.codeSize = desc.code_size;

    if (vkCreateShaderModule(*device_, &create_info, nullptr, &shader_) != VK_SUCCESS) has_error_ = true;
}

VulkanShader::~VulkanShader() { vkDestroyShaderModule(*device_, shader_, nullptr); }
}} // namespace tigine::graphic