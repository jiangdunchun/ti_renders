#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_PROGRAM_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_PROGRAM_H_

#include <string>
#include <vector>

#include "vulkan/vulkan_common.h"
#include "interface/i_shader_program.h"

namespace tigine { namespace graphic {
class VulkanShaderProgram : public IShaderProgram {
public:
    VulkanShaderProgram(const ShaderProgramDescriptor &desc);
    ~VulkanShaderProgram();

    bool                                         hasError() const override { return false; }
    std::string                                  getReport() const override { return "getReport() is not support in vulkan"; }
    std::vector<VkPipelineShaderStageCreateInfo> getVKShaderStageCreateInfos() { return vk_shader_stage_create_info_; }

private:
    std::vector<VkPipelineShaderStageCreateInfo> vk_shader_stage_create_info_;
};

}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_
