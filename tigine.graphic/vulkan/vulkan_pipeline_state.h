#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_PIPELINE_STATE_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_PIPELINE_STATE_H_

#include "vulkan/vulkan_common.h"
#include "interface/i_pipeline_state.h"

namespace tigine { namespace graphic {
class VulkanPipelineState : public IPipelineState {
public:
    VulkanPipelineState(const PipelineStateDescriptor &desc) : IPipelineState(desc) {}
    ~VulkanPipelineState() = default;
    DISALLOW_COPY_AND_ASSIGN(VulkanPipelineState);

private:
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_PIPELINE_STATE_H_
