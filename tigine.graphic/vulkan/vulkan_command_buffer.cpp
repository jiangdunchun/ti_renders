#include "vulkan/vulkan_command_buffer.h"


namespace tigine { namespace graphic {
VulkanCommandBuffer::VulkanCommandBuffer(VkDevice *vk_device, const CommandBufferDescriptor &desc) : vk_device_(vk_device) {}

VulkanCommandBuffer::~VulkanCommandBuffer() {}

void VulkanCommandBuffer::begin() {

}

void VulkanCommandBuffer::end() {

}

void VulkanCommandBuffer::setViewport(const Viewport &viewport) {

}

void VulkanCommandBuffer::setPipeState(IPipelineState *pipe_state) {

}

void VulkanCommandBuffer::setVertexBufferArray(IBufferArray *buffer_array) {

}

void VulkanCommandBuffer::beginRenderPass(IRenderPass *render_pass) {

}

void VulkanCommandBuffer::endRenderPass() {

}

void VulkanCommandBuffer::drawArray(TULong num_vertices, TULong first_vertex) {

}

void VulkanCommandBuffer::clear(TChar clear_flags) {

}
}} // namespace tigine::graphic
