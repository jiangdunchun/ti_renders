#ifndef TIGINE_RHI_VULKAN_VULKAN_PIPELINE_STATE_H_
#define TIGINE_RHI_VULKAN_VULKAN_PIPELINE_STATE_H_

#include "interface/i_pipeline_state.h"

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanPipelineState : public IPipelineState {
public:
    VulkanPipelineState(VkDevice *vk_device, const PipelineStateDesc &desc);
    ~VulkanPipelineState();

    VkPipeline *getVkPipeline() { return &vk_pipeline_; }

private:
    VkDevice *vk_device_;

    VkPipeline vk_pipeline_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_PIPELINE_STATE_H_
