#include "vulkan/vulkan_command_buffer.h"

#include <stdexcept>

#include "vulkan_buffer_array.h"
#include "vulkan_pipeline_state.h"


namespace tigine { namespace graphic {
VulkanCommandBuffer::VulkanCommandBuffer(VkDevice                      *vk_device,
                                         VkQueue                       *vk_graphics_queue,
                                         uint32_t                       vk_queue_family_index,
                                         const CommandBufferDescriptor &desc)
    : vk_device_(vk_device), buffers_count_(desc.buffer_count) {
    VkCommandPoolCreateInfo pool_info {};
    pool_info.sType             = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pool_info.pNext             = nullptr;
    pool_info.flags             = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    pool_info.queueFamilyIndex  = vk_queue_family_index;
    if (vkCreateCommandPool(*vk_device_, &pool_info, nullptr, &vk_command_pool_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }

    vk_command_buffers_.resize(buffers_count_);
    VkCommandBufferAllocateInfo alloc_info {};
    alloc_info.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    alloc_info.commandPool        = vk_command_pool_;
    alloc_info.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    alloc_info.commandBufferCount = buffers_count_;
    if (vkAllocateCommandBuffers(*vk_device_, &alloc_info, vk_command_buffers_.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffer!");
    }

    vk_fences_.resize(buffers_count_);
    VkFenceCreateInfo fence_info {};
    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_info.flags = 0;
    for (size_t i = 0; i < buffers_count_; i++) {
        if (vkCreateFence(*vk_device_, &fence_info, nullptr, &(vk_fences_[i])) != VK_SUCCESS) {
            throw std::runtime_error("failed to create fence of command buffer!");
        }
        vkQueueSubmit(*vk_graphics_queue, 0, nullptr, vk_fences_[i]);
    }

    acquireNextBuffer();
}

VulkanCommandBuffer::~VulkanCommandBuffer() { 
    for (size_t i = 0; i < vk_fences_.size(); i++) {
        vkDestroyFence(*vk_device_, vk_fences_[i], nullptr);
    }

    vkFreeCommandBuffers(*vk_device_, vk_command_pool_, static_cast<uint32_t>(vk_command_buffers_.size()), vk_command_buffers_.data());

    vkDestroyCommandPool(*vk_device_, vk_command_pool_, nullptr);
}

void VulkanCommandBuffer::begin() {
    acquireNextBuffer();

    vkWaitForFences(*vk_device_, 1, vk_now_fence_, VK_TRUE, UINT64_MAX);
    vkResetFences(*vk_device_, 1, vk_now_fence_);

    VkCommandBufferBeginInfo begin_info {};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(*vk_now_command_buffer_, &begin_info) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    vk_render_pass_info_ = {};
    vk_render_pass_info_.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
}

void VulkanCommandBuffer::end() {
    if (vkEndCommandBuffer(*vk_now_command_buffer_) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

void VulkanCommandBuffer::setViewport(const Viewport &viewport) { 
    vk_render_pass_info_.renderArea.offset = {static_cast<int32_t>(viewport.x), static_cast<int32_t>(viewport.y)};
    vk_render_pass_info_.renderArea.extent = {static_cast<uint32_t>(viewport.width), static_cast<uint32_t>(viewport.height)};
}

void VulkanCommandBuffer::setPipeState(IPipelineState *pipe_state) {
    VulkanPipelineState * vulkan_pipeline_state = dynamic_cast<VulkanPipelineState *>(pipe_state);
    vkCmdBindPipeline(*vk_now_command_buffer_, VK_PIPELINE_BIND_POINT_GRAPHICS, *(vulkan_pipeline_state->getVkPipeline()));

    ClearValue clear_value = pipe_state->get_clear_value();
    std::vector<VkClearValue> vk_clear_value(2);
    vk_clear_value[0].color = {clear_value.color[0], clear_value.color[1], clear_value.color[2], clear_value.color[3]};
    vk_clear_value[1].depthStencil = {clear_value.depth, clear_value.stencil};
    vk_render_pass_info_.clearValueCount = 2;
    vk_render_pass_info_.pClearValues    = &vk_clear_value[0];
}

void VulkanCommandBuffer::setVertexBufferArray(IBufferArray *buffer_array) {
    VulkanBufferArray *vulkan_buffer_array = dynamic_cast<VulkanBufferArray *>(buffer_array);

    vk_draw_indexed_ = vulkan_buffer_array->hasIndices();
}

void VulkanCommandBuffer::beginRenderPass(IRenderTarget *render_target, IRenderPass *render_pass) {

}

void VulkanCommandBuffer::endRenderPass() {

}

void VulkanCommandBuffer::drawArray(TULong num_vertices, TULong first_vertex) {
    //if (vk_draw_indexed_) vkCmdDrawIndexed(vk_command_buffer_, num_vertices, 1, first_vertex, 0, 0);
    //else vkCmdDraw(vk_command_buffer_, num_vertices, 1, first_vertex, 0);
}

void VulkanCommandBuffer::clear(TChar clear_flags) {

}

void VulkanCommandBuffer::acquireNextBuffer() {
    vk_now_command_buffer_ = &(vk_command_buffers_[buffers_next_index_]);
    vk_now_fence_          = &(vk_fences_[buffers_next_index_]);
    buffers_next_index_    = (buffers_next_index_ + 1) % buffers_count_;
}
}} // namespace tigine::graphic
