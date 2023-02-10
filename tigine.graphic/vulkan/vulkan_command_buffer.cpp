#include "vulkan/vulkan_command_buffer.h"

#include <stdexcept>

#include "vulkan_buffer_array.h"


namespace tigine { namespace graphic {
VulkanCommandBuffer::VulkanCommandBuffer(VkDevice *vk_device, VkCommandPool *vk_command_pool, const CommandBufferDescriptor &desc)
    : vk_device_(vk_device), vk_command_pool_(vk_command_pool) {
    VkCommandBufferAllocateInfo alloc_info {};
    alloc_info.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    alloc_info.commandPool        = *vk_command_pool_;
    alloc_info.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    alloc_info.commandBufferCount = 1;
    if (vkAllocateCommandBuffers(*vk_device_, &alloc_info, &vk_command_buffer_) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

VulkanCommandBuffer::~VulkanCommandBuffer() { 
    vkFreeCommandBuffers(*vk_device_, *vk_command_pool_, 1, &vk_command_buffer_);
}

void VulkanCommandBuffer::begin() {
    VkCommandBufferBeginInfo begin_info {};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(vk_command_buffer_, &begin_info) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }
}

void VulkanCommandBuffer::end() {
    if (vkEndCommandBuffer(vk_command_buffer_) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

void VulkanCommandBuffer::setViewport(const Viewport &viewport) {
}

void VulkanCommandBuffer::setPipeState(IPipelineState *pipe_state) {

}

void VulkanCommandBuffer::setVertexBufferArray(IBufferArray *buffer_array) {
    VulkanBufferArray *vulkan_buffer_array = dynamic_cast<VulkanBufferArray *>(buffer_array);
}

void VulkanCommandBuffer::beginRenderPass(IRenderPass *render_pass) {

}

void VulkanCommandBuffer::endRenderPass() {

}

void VulkanCommandBuffer::drawArray(TULong num_vertices, TULong first_vertex) {
    vkCmdDraw(vk_command_buffer_, num_vertices, 1, first_vertex, 0);
}

void VulkanCommandBuffer::clear(TChar clear_flags) {

}
}} // namespace tigine::graphic
