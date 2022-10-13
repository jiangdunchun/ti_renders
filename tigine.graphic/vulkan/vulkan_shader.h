#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_

#include "vulkan/vulkan_common.h"
#include "interface/i_shader.h"

namespace tigine { namespace graphic {
class VulkanShader : public IShader {
public:
    VulkanShader(VkDevice *device, const ShaderDescriptor &desc) : device_(device) {
        VkShaderModuleCreateInfo create_info {};
        create_info.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        create_info.pCode    = reinterpret_cast<const uint32_t *>(desc.code);
        create_info.codeSize = desc.code_size;

        if (vkCreateShaderModule(*device_, &create_info, nullptr, &shader_) != VK_SUCCESS) has_error_ = true;
    }

    ~VulkanShader() { vkDestroyShaderModule(*device_, shader_, nullptr); }

    bool        hasError() const { return has_error_; }
    std::string getReport() const { return ""; }
    VkShaderModule getShaderModule() { return shader_; }

private:
    VkDevice      *device_;
    VkShaderModule shader_;
    bool           has_error_ = false;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_
