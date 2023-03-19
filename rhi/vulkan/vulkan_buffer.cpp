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

VulkanBuffer::VulkanBuffer(VkPhysicalDevice *vk_physical_device, VkDevice *vk_device, const BufferDesc &desc) 
    : data_size_(desc.data_size), vk_physical_device_(vk_physical_device), vk_device_(vk_device) {
    VkBufferUsageFlags vk_usage = mapVkBufferKind(desc.kind);
    VkMemoryPropertyFlags mem_properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    createVkBufferandDeviceMemory(vk_physical_device_, vk_device, desc.data_size, vk_usage, mem_properties, vk_buffer_, vk_device_memory_);

    if (desc.data) {
        updateData(desc.data_size, desc.data);
    }
}

VulkanBuffer::~VulkanBuffer() { 
    vkFreeMemory(*vk_device_, vk_device_memory_, nullptr);
    vkDestroyBuffer(*vk_device_, vk_buffer_, nullptr);
}

void VulkanBuffer::updateData(TULong data_size, void *data) {
    void *dst_ptr;
    vkMapMemory(*vk_device_, vk_device_memory_, 0, data_size, 0, &dst_ptr);
    memcpy(dst_ptr, data, (size_t)data_size);
    vkUnmapMemory(*vk_device_, vk_device_memory_);
}
}} // namespace tigine::rhi
