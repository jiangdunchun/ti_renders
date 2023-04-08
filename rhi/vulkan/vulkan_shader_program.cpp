#include "vulkan/vulkan_shader_program.h"

#include "vulkan/vulkan_shader.h"

namespace tigine { namespace rhi {
VulkanShaderProgram::VulkanShaderProgram(const VulkanContextInfo &context, const ShaderProgramDesc &desc) {
    if (desc.vertex_shader) {
        VkPipelineShaderStageCreateInfo vk_shader_info {};
        vk_shader_info.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vk_shader_info.stage  = VK_SHADER_STAGE_VERTEX_BIT;
        vk_shader_info.module = *(dynamic_cast<VulkanShader *>(desc.vertex_shader)->getVKShaderModule());
        vk_shader_info.pName  = "main";

        vk_shader_stage_create_infos_.push_back(vk_shader_info);
    }
    if (desc.fragment_shader) {
        VkPipelineShaderStageCreateInfo vk_shader_info {};
        vk_shader_info.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vk_shader_info.stage  = VK_SHADER_STAGE_FRAGMENT_BIT;
        vk_shader_info.module = *(dynamic_cast<VulkanShader *>(desc.fragment_shader)->getVKShaderModule());
        vk_shader_info.pName  = "main";

        vk_shader_stage_create_infos_.push_back(vk_shader_info);
    }
    if (desc.compute_shader) {
        VkPipelineShaderStageCreateInfo vk_shader_info {};
        vk_shader_info.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vk_shader_info.stage  = VK_SHADER_STAGE_COMPUTE_BIT;
        vk_shader_info.module = *(dynamic_cast<VulkanShader *>(desc.compute_shader)->getVKShaderModule());
        vk_shader_info.pName  = "main";

        vk_shader_stage_create_infos_.push_back(vk_shader_info);
    }
}

VulkanShaderProgram::~VulkanShaderProgram() {}
}} // namespace tigine::rhi
