#include "vulkan/vulkan_shader_program.h"

#include "vulkan/vulkan_shader.h"

namespace tigine { namespace rhi {
VulkanShaderProgram::VulkanShaderProgram(const VulkanContextInfo &context, const ShaderProgramDesc &desc) {
    if (desc.vertex_shader) {
        VkPipelineShaderStageCreateInfo shaderStageInfo {};
        shaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        shaderStageInfo.stage  = VK_SHADER_STAGE_VERTEX_BIT;
        shaderStageInfo.module = *(dynamic_cast<VulkanShader *>(desc.vertex_shader)->getVKShaderModule());
        shaderStageInfo.pName  = "main";

        vk_shader_stage_create_info_.push_back(shaderStageInfo);
    }
    if (desc.fragment_shader) {
        VkPipelineShaderStageCreateInfo shaderStageInfo {};
        shaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        shaderStageInfo.stage  = VK_SHADER_STAGE_FRAGMENT_BIT;
        shaderStageInfo.module = *(dynamic_cast<VulkanShader *>(desc.fragment_shader)->getVKShaderModule());
        shaderStageInfo.pName  = "main";

        vk_shader_stage_create_info_.push_back(shaderStageInfo);
    }
    if (desc.compute_shader) {
        VkPipelineShaderStageCreateInfo shaderStageInfo {};
        shaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        shaderStageInfo.stage  = VK_SHADER_STAGE_COMPUTE_BIT;
        shaderStageInfo.module = *(dynamic_cast<VulkanShader *>(desc.compute_shader)->getVKShaderModule());
        shaderStageInfo.pName  = "main";

        vk_shader_stage_create_info_.push_back(shaderStageInfo);
    }
}

VulkanShaderProgram::~VulkanShaderProgram() {}
}} // namespace tigine::rhi
