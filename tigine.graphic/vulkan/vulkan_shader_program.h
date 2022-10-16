#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_PROGRAM_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_PROGRAM_H_

#include <map>
#include <string>
#include <vector>

#include "vulkan/vulkan_common.h"
#include "interface/i_shader_program.h"

#include "vulkan/vulkan_shader.h"

namespace tigine { namespace graphic {
class VulkanShaderProgram : public IShaderProgram {
public:
    VulkanShaderProgram(const ShaderProgramDescriptor& desc) {
        if (desc.vertex_shader) {
            VkPipelineShaderStageCreateInfo shaderStageInfo {};
            shaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            shaderStageInfo.stage  = VK_SHADER_STAGE_VERTEX_BIT;
            shaderStageInfo.module = static_cast<VulkanShader *>(desc.vertex_shader)->getShaderModule();
            shaderStageInfo.pName  = "main";

            shader_stage_create_info_.push_back(shaderStageInfo);
        }
        if (desc.fragment_shader) {
            VkPipelineShaderStageCreateInfo shaderStageInfo {};
            shaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            shaderStageInfo.stage  = VK_SHADER_STAGE_FRAGMENT_BIT;
            shaderStageInfo.module = static_cast<VulkanShader *>(desc.fragment_shader)->getShaderModule();
            shaderStageInfo.pName  = "main";

            shader_stage_create_info_.push_back(shaderStageInfo);
        }
        if (desc.compute_shader) {
            VkPipelineShaderStageCreateInfo shaderStageInfo {};
            shaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            shaderStageInfo.stage  = VK_SHADER_STAGE_COMPUTE_BIT;
            shaderStageInfo.module = static_cast<VulkanShader *>(desc.compute_shader)->getShaderModule();
            shaderStageInfo.pName  = "main";

            shader_stage_create_info_.push_back(shaderStageInfo);
        }
    }
    ~VulkanShaderProgram() {}

    bool                                         hasError() const override { return false; }
    std::string                                  getReport() const override { return "getReport() is not support in vulkan"; }
    std::vector<VkPipelineShaderStageCreateInfo> getShaderStageCreateInfo() { return shader_stage_create_info_; }

private:
    std::vector<VkPipelineShaderStageCreateInfo> shader_stage_create_info_;
};

}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_SHADER_H_
