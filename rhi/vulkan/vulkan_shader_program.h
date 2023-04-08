#ifndef TIGINE_RHI_VULKAN_VULKAN_SHADER_PROGRAM_H_
#define TIGINE_RHI_VULKAN_VULKAN_SHADER_PROGRAM_H_

#include "interface/i_shader_program.h"

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanShaderProgram : public IShaderProgram {
public:
    VulkanShaderProgram(const VulkanContextInfo &context, const ShaderProgramDesc &desc);
    ~VulkanShaderProgram();

    bool    hasError() const override { return false; }
    TString getReport() const override { return "getReport() is not support in vulkan"; }

    TUInt                            getVKShaderStageCreateInfosCount() { return vk_shader_stage_create_infos_.size(); }
    VkPipelineShaderStageCreateInfo *getVKShaderStageCreateInfos() { return vk_shader_stage_create_infos_.data(); }

private:
    std::vector<VkPipelineShaderStageCreateInfo> vk_shader_stage_create_infos_;
};

}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_SHADER_H_
