#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_QUEUE_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_QUEUE_H_

#include "vulkan/vulkan_common.h"

#include "interface/i_command_queue.h"

namespace tigine { namespace graphic {
class VulkanCommandQueue : public ICommandQueue {
public:
    void submit(ICommandBuffer *command_buffer) override {}

private:
    VkCommandPool *command_pool_ = nullptr;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_QUEUE_H_
