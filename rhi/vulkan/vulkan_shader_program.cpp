#include "vulkan/vulkan_shader_program.h"

#include "vulkan/vulkan_shader.h"

namespace tigine { namespace rhi {
VulkanShaderProgram::VulkanShaderProgram(const VulkanContextInfo &context, const ShaderProgramDesc &desc) {
    VkPipelineShaderStageCreateInfo vk_stage_info {};
    vk_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vk_stage_info.pName = "main";

    if (desc.vertex_shader) {
        vk_stage_info.stage  = VK_SHADER_STAGE_VERTEX_BIT;
        vk_stage_info.module = *(dynamic_cast<VulkanShader *>(desc.vertex_shader)->getVKShaderModule());

        vk_shader_stage_create_infos_.push_back(vk_stage_info);
    }
    if (desc.fragment_shader) {
        vk_stage_info.stage  = VK_SHADER_STAGE_FRAGMENT_BIT;
        vk_stage_info.module = *(dynamic_cast<VulkanShader *>(desc.fragment_shader)->getVKShaderModule());

        vk_shader_stage_create_infos_.push_back(vk_stage_info);
    }
    if (desc.compute_shader) {
        vk_stage_info.stage  = VK_SHADER_STAGE_COMPUTE_BIT;
        vk_stage_info.module = *(dynamic_cast<VulkanShader *>(desc.compute_shader)->getVKShaderModule());

        vk_shader_stage_create_infos_.push_back(vk_stage_info);
    }
}

VulkanShaderProgram::~VulkanShaderProgram() {}
}} // namespace tigine::rhi
