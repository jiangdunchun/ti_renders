#include "vulkan/vulkan_buffer.h"

#include <string>
#include <stdexcept>

namespace tigine { namespace graphic {
namespace {
VkBufferUsageFlags mapBufferKinds(std::uint32_t kinds) {
    VkBufferUsageFlags type = 0;
    if ((kinds & BK_Vertices) > 0) type |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    if ((kinds & BK_Indices) > 0) type |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    return type;
}

uint32_t findMemoryType(VkPhysicalDevice *physical_divece, uint32_t type_filter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(*physical_divece, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((type_filter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}
} // namespace

VulkanBuffer::VulkanBuffer(VkPhysicalDevice *physical_divece, VkDevice *device, const BufferDescriptor &desc) 
    : data_size_(desc.data_size), physical_divece_(physical_divece), device_(device) {
    VkBufferCreateInfo buffer_create_info    = {};
    buffer_create_info.sType                 = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buffer_create_info.pNext                 = NULL;
    buffer_create_info.usage                 = mapBufferKinds(desc.kinds);
    buffer_create_info.size                  = desc.data_size;
    buffer_create_info.queueFamilyIndexCount = 0;
    buffer_create_info.pQueueFamilyIndices   = NULL;
    buffer_create_info.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
    buffer_create_info.flags                 = 0;
    vkCreateBuffer(*device_, &buffer_create_info, NULL, &buffer_);

    VkMemoryRequirements mem_requirements;
    vkGetBufferMemoryRequirements(*device, buffer_, &mem_requirements);
    VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    VkMemoryAllocateInfo memory_allocate_info = {};
    memory_allocate_info.sType                = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memory_allocate_info.allocationSize       = mem_requirements.size;
    memory_allocate_info.memoryTypeIndex      = findMemoryType(physical_divece, mem_requirements.memoryTypeBits, properties);
    vkAllocateMemory(*device_, &memory_allocate_info, nullptr, &memory_);

    vkBindBufferMemory(*device_, buffer_, memory_, 0);
    if (desc.data) {
        updateData(desc.data_size, desc.data);
    }
}

VulkanBuffer::~VulkanBuffer() { 
    vkDestroyBuffer(*device_, buffer_, nullptr);
    vkFreeMemory(*device_, memory_, nullptr);
}

void VulkanBuffer::updateData(TULong data_size, void *data) {
    void *dst_ptr;
    vkMapMemory(*device_, memory_, 0, data_size, 0, &dst_ptr);
    memcpy(dst_ptr, data, (size_t)data_size);
    vkUnmapMemory(*device_, memory_);
}
}
} // namespace tigine
