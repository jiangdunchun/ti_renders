#include "vulkan/vulkan_command_buffer.h"

#include <stdexcept>

#include "vulkan_buffer_array.h"
#include "vulkan_pipeline_state.h"


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

    vk_render_pass_info_ = {};
    vk_render_pass_info_.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
}

void VulkanCommandBuffer::end() {
    if (vkEndCommandBuffer(vk_command_buffer_) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

void VulkanCommandBuffer::setViewport(const Viewport &viewport) { 
    vk_render_pass_info_.renderArea.offset = {static_cast<int32_t>(viewport.x), static_cast<int32_t>(viewport.y)};
    vk_render_pass_info_.renderArea.extent = {static_cast<uint32_t>(viewport.width), static_cast<uint32_t>(viewport.height)};
}

void VulkanCommandBuffer::setPipeState(IPipelineState *pipe_state) {
    VulkanPipelineState * vulkan_pipeline_state = dynamic_cast<VulkanPipelineState *>(pipe_state);
    vkCmdBindPipeline(vk_command_buffer_, VK_PIPELINE_BIND_POINT_GRAPHICS, *(vulkan_pipeline_state->getVkPipeline()));

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

void VulkanCommandBuffer::beginRenderPass(IRenderPass *render_pass) {

}

void VulkanCommandBuffer::endRenderPass() {

}

void VulkanCommandBuffer::drawArray(TULong num_vertices, TULong first_vertex) {
    //if (vk_draw_indexed_) vkCmdDrawIndexed(vk_command_buffer_, num_vertices, 1, first_vertex, 0, 0);
    //else vkCmdDraw(vk_command_buffer_, num_vertices, 1, first_vertex, 0);
}

void VulkanCommandBuffer::clear(TChar clear_flags) {

}
}} // namespace tigine::graphic
