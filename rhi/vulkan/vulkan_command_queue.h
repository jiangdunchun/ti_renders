#ifndef TIGINE_RHI_VULKAN_VULKAN_COMMAND_QUEUE_H_
#define TIGINE_RHI_VULKAN_VULKAN_COMMAND_QUEUE_H_

#include "interface/i_command_queue.h"

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanCommandQueue : public ICommandQueue {
public:
    VulkanCommandQueue(VkQueue *vk_graphics_queue);
    ~VulkanCommandQueue();

    void submit(ICommandBuffer *command_buffer) override;

private:
    VkQueue  *vk_graphics_queue_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_COMMAND_QUEUE_H_
