#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_PIPELINE_STATE_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_PIPELINE_STATE_H_

#include "interface/i_pipeline_state.h"

#include "vulkan/vulkan_common.h"


namespace tigine { namespace graphic {
class VulkanPipelineState : public IPipelineState {
public:
    VulkanPipelineState(VkDevice *vk_device, const PipelineStateDescriptor &desc);
    ~VulkanPipelineState();

private:
    VkDevice *vk_device_;

    VkPipeline vk_pipeline_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_PIPELINE_STATE_H_
