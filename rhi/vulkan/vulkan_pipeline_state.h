#ifndef TIGINE_RHI_VULKAN_VULKAN_PIPELINE_STATE_H_
#define TIGINE_RHI_VULKAN_VULKAN_PIPELINE_STATE_H_

#include "interface/i_pipeline_state.h"

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanResourceHeap;
class VulkanPipelineState : public IPipelineState {
public:
    VulkanPipelineState(const VulkanContextInfo &context, const PipelineStateDesc &desc);
    ~VulkanPipelineState();

    VkPipeline *getVkPipeline() { return &vk_pipeline_; }
    VulkanResourceHeap *getVulkanResourceHeap() { return vulkan_resource_heap_; }

private:
    VkDevice *vk_device_;

    VulkanResourceHeap *vulkan_resource_heap_;

    VkPipeline vk_pipeline_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_PIPELINE_STATE_H_
