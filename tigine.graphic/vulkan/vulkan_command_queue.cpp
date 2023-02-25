#include "vulkan/vulkan_command_queue.h"

#include <stdexcept>

#include "vulkan_command_buffer.h"


namespace tigine { namespace graphic {
VulkanCommandQueue::VulkanCommandQueue(VkDevice *vk_device, VkQueue *vk_graphics_queue, uint32_t graphics_family) 
    : vk_device_(vk_device), vk_graphics_queue_(vk_graphics_queue) {
}

VulkanCommandQueue::~VulkanCommandQueue() { }

void VulkanCommandQueue::submit(ICommandBuffer* command_buffer) {
    VulkanCommandBuffer *vulkan_command_buffer = dynamic_cast<VulkanCommandBuffer *>(command_buffer);

    VkSubmitInfo submit_info {};
    submit_info.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.pNext                = nullptr;
    submit_info.waitSemaphoreCount   = 0;
    submit_info.pWaitSemaphores      = nullptr;
    submit_info.pWaitDstStageMask    = 0;
    submit_info.commandBufferCount   = 1;
    submit_info.pCommandBuffers      = vulkan_command_buffer->getVKCommandBuffer();
    submit_info.signalSemaphoreCount = 0;
    submit_info.pSignalSemaphores    = nullptr;
    if (vkQueueSubmit(*vk_graphics_queue_, 1, &submit_info, *(vulkan_command_buffer->getVKQueueSubmitFence())) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit command buffer to Vulkan graphics queue!");
    }
}
}} // namespace tigine::graphic
