#include "vulkan/vulkan_command_queue.h"

#include <stdexcept>


namespace tigine { namespace graphic {
VulkanCommandQueue::VulkanCommandQueue(VkDevice *vk_device, uint32_t graphics_family) : vk_device_(vk_device) {
    VkCommandPoolCreateInfo poolInfo {};
    poolInfo.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = graphics_family;

    if (vkCreateCommandPool(*vk_device_, &poolInfo, nullptr, &vk_command_pool_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
}

VulkanCommandQueue::~VulkanCommandQueue() { 
    vkDestroyCommandPool(*vk_device_, vk_command_pool_, nullptr);
}

void VulkanCommandQueue::submit(ICommandBuffer* command_buffer) {

}
}} // namespace tigine::graphic
