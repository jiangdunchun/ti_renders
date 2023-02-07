#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_QUEUE_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_QUEUE_H_

#include "interface/i_command_queue.h"

#include "vulkan/vulkan_common.h"


namespace tigine { namespace graphic {
class VulkanCommandQueue : public ICommandQueue {
public:
    VulkanCommandQueue(VkDevice *vk_device, uint32_t graphics_family);
    ~VulkanCommandQueue();

    void submit(ICommandBuffer *command_buffer) override;

    VkCommandPool *getVkCommandPool() { return &vk_command_pool_; }

private:
    VkDevice     *vk_device_;

    VkCommandPool vk_command_pool_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_QUEUE_H_
