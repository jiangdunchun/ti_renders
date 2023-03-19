#include "vulkan/vulkan_command_buffer.h"

#include "vulkan/vulkan_buffer.h"
#include "vulkan/vulkan_buffer_array.h"
#include "vulkan/vulkan_pipeline_state.h"
#include "vulkan/vulkan_render_context.h"
#include "vulkan/vulkan_render_pass.h"
#include "vulkan/vulkan_resource_heap.h"

namespace tigine { namespace rhi {
namespace {
VkIndexType mapVkIndexType(IndexKind kind) {
    switch (kind) {
    case IndexKind::IK_UINT16:
        return VK_INDEX_TYPE_UINT16;
    case IndexKind::IK_UINT32:
        return VK_INDEX_TYPE_UINT32;
    default:
        RHI_VULKAN_THROW("faild to map VkIndexType!");
    }
}
} // namespace
VulkanCommandBuffer::VulkanCommandBuffer(VkDevice                      *vk_device,
                                         VkQueue                       *vk_graphics_queue,
                                         uint32_t                       vk_queue_family_index,
                                         const CommandBufferDesc &desc)
    : vk_device_(vk_device), buffers_count_(desc.buffer_count) {
    vk_command_buffers_.resize(buffers_count_);
    createVkCommandPoolandCommandBuffers(vk_device_, 
                                         vk_queue_family_index, 
                                         buffers_count_, 
                                         vk_command_pool_, 
                                         vk_command_buffers_.data());

    vk_fences_.resize(buffers_count_);
    VkFenceCreateInfo fence_info {};
    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_info.flags = 0;
    for (size_t i = 0; i < buffers_count_; i++) {
        RHI_VULKAN_THROW_IF_FAILD(vkCreateFence(*vk_device_, &fence_info, nullptr, &(vk_fences_[i])),
            "failed to create fence of command buffer!");
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
    RHI_VULKAN_THROW_IF_FAILD(vkBeginCommandBuffer(*vk_now_command_buffer_, &begin_info),
        "failed to begin recording command buffer!");

    //vk_render_pass_info_ = {};
    //vk_render_pass_info_.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
}

void VulkanCommandBuffer::end() {
    RHI_VULKAN_THROW_IF_FAILD(vkEndCommandBuffer(*vk_now_command_buffer_),
        "failed to record command buffer!");
}

void VulkanCommandBuffer::setViewport(const Viewport &viewport) { 
    //vk_render_pass_info_.renderArea.offset = {static_cast<int32_t>(viewport.x), static_cast<int32_t>(viewport.y)};
    //vk_render_pass_info_.renderArea.extent = {static_cast<uint32_t>(viewport.width), static_cast<uint32_t>(viewport.height)};

    VkViewport vk_viewport {viewport.x, viewport.y, viewport.width, viewport.height};
    vkCmdSetViewport(*vk_now_command_buffer_, 0, 1, &vk_viewport);
}

void VulkanCommandBuffer::setPipeState(IPipelineState *pipe_state) {
    //VulkanPipelineState * vulkan_pipeline_state = dynamic_cast<VulkanPipelineState *>(pipe_state);
    //vkCmdBindPipeline(*vk_now_command_buffer_, VK_PIPELINE_BIND_POINT_GRAPHICS, *(vulkan_pipeline_state->getVkPipeline()));

    //ClearValue clear_value = pipe_state->get_clear_value();
    //std::vector<VkClearValue> vk_clear_value(2);
    //vk_clear_value[0].color = {clear_value.color[0], clear_value.color[1], clear_value.color[2], clear_value.color[3]};
    //vk_clear_value[1].depthStencil = {clear_value.depth, clear_value.stencil};
    //vk_render_pass_info_.clearValueCount = 2;
    //vk_render_pass_info_.pClearValues    = &vk_clear_value[0];


    VulkanPipelineState *vulkan_pipeline_state = dynamic_cast<VulkanPipelineState *>(pipe_state);
    VkPipeline          *vk_pipeline           = vulkan_pipeline_state->getVkPipeline();

    vkCmdBindPipeline(*vk_now_command_buffer_, VK_PIPELINE_BIND_POINT_GRAPHICS, *(vk_pipeline));


    VulkanResourceHeap *vulkan_resource_heap = vulkan_pipeline_state->getVulkanResourceHeap();
    VkPipelineLayout   *vk_pipeline_layout   = vulkan_resource_heap->getVkPipelineLayout();
    VkDescriptorSet    *vk_descriptor_set    = vulkan_resource_heap->getVkDescriptorSet();

    vkCmdBindDescriptorSets(*vk_now_command_buffer_,
                             VK_PIPELINE_BIND_POINT_GRAPHICS,
                            *vk_pipeline_layout,
                             0,
                             1,
                             vk_descriptor_set,
                             0,
                             nullptr);
}

void VulkanCommandBuffer::setVertexBufferArray(IBufferArray *buffer_array) {
    VulkanBufferArray *vulkan_buffer_array = dynamic_cast<VulkanBufferArray *>(buffer_array);

    draw_indexed_ = vulkan_buffer_array->hasIndices();

    VkBuffer    *vertices_buffer = vulkan_buffer_array->getVerticesBuffer()->getVkBuffer();
    VkDeviceSize offsets[]       = {0};
    vkCmdBindVertexBuffers(*vk_now_command_buffer_, 0, 1, vertices_buffer, offsets);

    if (draw_indexed_) {
        VkBuffer *indices_buffer = vulkan_buffer_array->getIndicesBuffer()->getVkBuffer();
        VkIndexType index_type   = mapVkIndexType(vulkan_buffer_array->GetIndexKind());
        vkCmdBindIndexBuffer(*vk_now_command_buffer_, *indices_buffer, 0, index_type);
    }
}

void VulkanCommandBuffer::beginRenderPass(IRenderTarget *render_target, IRenderPass *render_pass) {
    VulkanRenderPass *vulkan_render_pass = dynamic_cast<VulkanRenderPass *>(render_pass);
    if (render_target->isContext()) {
        VulkanRenderContext *render_context = dynamic_cast<VulkanRenderContext *>(render_target);
        
        // @TODO
        VkClearValue          clear_cc = {0, 0, 0, 1};
        VkRenderPassBeginInfo begin_info;
        {
            begin_info.sType             = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            begin_info.pNext             = nullptr;
            begin_info.renderPass        = *(vulkan_render_pass->getVkRenderPass());
            begin_info.framebuffer       = *(render_context->getVkFrameBuffer());
            begin_info.renderArea.offset = {0, 0};
            begin_info.renderArea.extent = {render_context->getResolution().width, render_context->getResolution().height};
            begin_info.clearValueCount   = 1;
            begin_info.pClearValues      = &clear_cc;
        }
        vkCmdBeginRenderPass(*vk_now_command_buffer_, &begin_info, VK_SUBPASS_CONTENTS_INLINE);
    }
}

void VulkanCommandBuffer::endRenderPass() { 
    vkCmdEndRenderPass(*vk_now_command_buffer_);
}

void VulkanCommandBuffer::drawArray(TULong num_vertices, TULong first_vertex) {
    if (draw_indexed_) {
        vkCmdDrawIndexed(*vk_now_command_buffer_, num_vertices, 1, first_vertex, 0, 0);
    } else {
        vkCmdDraw(*vk_now_command_buffer_, num_vertices, 1, first_vertex, 0); 
    }
}

void VulkanCommandBuffer::clear(TChar clear_flags) {
    //VkClearRect clearRect;
    //{
    //    clearRect.rect.offset.x  = 0;
    //    clearRect.rect.offset.y  = 0;
    //    clearRect.rect.extent    = framebufferExtent_;
    //    clearRect.baseArrayLayer = 0;
    //    clearRect.layerCount     = 1;
    //}
    //vkCmdClearAttachments(*vk_now_command_buffer_, numAttachments, attachments, 1, &clearRect);
}

void VulkanCommandBuffer::acquireNextBuffer() {
    vk_now_command_buffer_ = &(vk_command_buffers_[buffers_next_index_]);
    vk_now_fence_          = &(vk_fences_[buffers_next_index_]);
    buffers_next_index_    = (buffers_next_index_ + 1) % buffers_count_;
}
}} // namespace tigine::rhi
