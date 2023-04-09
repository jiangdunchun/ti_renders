#include "vulkan/vulkan_command_queue.h"

#include "vulkan/vulkan_command_buffer.h"

namespace tigine { namespace rhi {
VulkanCommandQueue::VulkanCommandQueue(const VulkanContextInfo &context)
    : vk_graphics_queue_(context.vk_graphics_queue) {}

VulkanCommandQueue::~VulkanCommandQueue() { }

void VulkanCommandQueue::submit(ICommandBuffer* command_buffer) {
    VulkanCommandBuffer *vulkan_command_buffer = dynamic_cast<VulkanCommandBuffer *>(command_buffer);
    VkCommandBuffer     *vk_command_buffer     = vulkan_command_buffer->getVKCommandBuffer();
    VkFence             *vk_fence              = vulkan_command_buffer->getVKQueueSubmitFence();

    VkSubmitInfo vk_submit_info {};
    vk_submit_info.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    vk_submit_info.pNext                = nullptr;
    vk_submit_info.waitSemaphoreCount   = 0;
    vk_submit_info.pWaitSemaphores      = nullptr;
    vk_submit_info.pWaitDstStageMask    = 0;
    vk_submit_info.commandBufferCount   = 1;
    vk_submit_info.pCommandBuffers      = vk_command_buffer;
    vk_submit_info.signalSemaphoreCount = 0;
    vk_submit_info.pSignalSemaphores    = nullptr;
    RHI_VULKAN_THROW_IF_FAILD(vkQueueSubmit(*vk_graphics_queue_, 1, &vk_submit_info, *(vk_fence)),
        "failed to submit command buffer to Vulkan graphics queue!");
}
}} // namespace tigine::rhi
