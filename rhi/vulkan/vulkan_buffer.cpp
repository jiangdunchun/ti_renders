#include "vulkan/vulkan_buffer.h"

namespace tigine { namespace rhi {
namespace {
VkBufferUsageFlags mapVkBufferKind(BufferKind kind) {
    switch (kind) {
    case BufferKind::Uniform:
        return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    case BufferKind::Vertices:
        return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    case BufferKind::Indices:
        return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    default:
        RHI_VULKAN_THROW("failed to map BufferKind!");
    }
}
} // namespace

VulkanBuffer::VulkanBuffer(const VulkanContextInfo &context, const BufferDesc &desc) 
    : vk_device_(context.vk_device), buffer_size_(desc.buffer_size) {
    VkBufferUsageFlags vk_usage_flags = mapVkBufferKind(desc.kind);
    VkMemoryPropertyFlags vk_memory_flags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    createVkBufferandDeviceMemory(context.vk_physical_device, 
                                  context.vk_device, 
                                  static_cast<VkDeviceSize>(buffer_size_), 
                                  vk_usage_flags, 
                                  vk_memory_flags,
                                  vk_buffer_,
                                  vk_device_memory_);

    if (desc.src_data.data) {
        updateData(desc.src_data);
    }
}

VulkanBuffer::~VulkanBuffer() { 
    vkFreeMemory(*vk_device_, vk_device_memory_, nullptr);
    vkDestroyBuffer(*vk_device_, vk_buffer_, nullptr);
}

void VulkanBuffer::updateData(const BufferDataDesc &desc) {
    void *dst_ptr;
    vkMapMemory(*vk_device_, vk_device_memory_, 0, static_cast<VkDeviceSize>(buffer_size_), 0, &dst_ptr);
    memcpy(dst_ptr, desc.data, static_cast<size_t>(desc.data_size));
    vkUnmapMemory(*vk_device_, vk_device_memory_);
}
}} // namespace tigine::rhi
