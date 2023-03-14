#include "vulkan/vulkan_buffer.h"

namespace tigine { namespace rhi {
namespace {
VkBufferUsageFlags mapVkBufferKind(BufferKind kind) {
    switch (kind) {
    case BufferKind::Vertices:
        return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    case BufferKind::Indices:
        return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    default:
        RHI_VULKAN_THROW("failed to map BufferKind!");
    }
}

uint32_t findMemoryType(VkPhysicalDevice *physical_divece, uint32_t type_filter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties mem_properties;
    vkGetPhysicalDeviceMemoryProperties(*physical_divece, &mem_properties);

    for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++) {
        if ((type_filter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    RHI_VULKAN_THROW("failed to find suitable memory type!");
}
} // namespace

VulkanBuffer::VulkanBuffer(VkPhysicalDevice *vk_physical_device, VkDevice *vk_device, const BufferDesc &desc) 
    : data_size_(desc.data_size), vk_physical_device_(vk_physical_device), vk_device_(vk_device) {
    VkBufferCreateInfo create_info {};
    create_info.sType                 = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    create_info.pNext                 = NULL;
    create_info.usage                 = mapVkBufferKind(desc.kind);
    create_info.size                  = desc.data_size;
    create_info.queueFamilyIndexCount = 0;
    create_info.pQueueFamilyIndices   = NULL;
    create_info.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
    create_info.flags                 = 0;
    RHI_VULKAN_THROW_IF_FAILD(vkCreateBuffer(*vk_device_, &create_info, NULL, &vk_buffer_), 
        "failed to create buffer!");

    VkMemoryRequirements mem_requirements {};
    vkGetBufferMemoryRequirements(*vk_device_, vk_buffer_, &mem_requirements);
    VkMemoryPropertyFlags mem_properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    VkMemoryAllocateInfo alloc_info {};
    alloc_info.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    alloc_info.allocationSize  = mem_requirements.size;
    alloc_info.memoryTypeIndex = findMemoryType(vk_physical_device_, mem_requirements.memoryTypeBits, mem_properties);
    RHI_VULKAN_THROW_IF_FAILD(vkAllocateMemory(*vk_device_, &alloc_info, nullptr, &vk_device_memory_), 
        "failed to allocate memory!");

    vkBindBufferMemory(*vk_device_, vk_buffer_, vk_device_memory_, 0);

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
