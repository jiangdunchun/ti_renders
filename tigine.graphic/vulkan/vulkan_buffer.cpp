#include "vulkan/vulkan_buffer.h"

#include <string>

namespace tigine { namespace graphic {
namespace {
VkBufferUsageFlags mapBufferKinds(std::uint32_t kinds) {
    VkBufferUsageFlags type = 0;
    if ((kinds & BK_Vertices) > 0) type |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    if ((kinds & BK_Indices) > 0) type |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    return type;
}
} // namespace

VulkanBuffer::VulkanBuffer(VkDevice *device, const BufferDescriptor &desc) : device_(device) {
    VkBufferCreateInfo create_info    = {};
    create_info.sType                 = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    create_info.pNext                 = NULL;
    create_info.usage                 = mapBufferKinds(desc.kinds);
    create_info.size                  = desc.data_size;
    create_info.queueFamilyIndexCount = 0;
    create_info.pQueueFamilyIndices   = NULL;
    create_info.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
    create_info.flags                 = 0;

    vkCreateBuffer(*device_, &create_info, NULL, &buffer_);

    if (desc.data) {
        void *data;
        vkMapMemory(*device_, memory_, 0, desc.data_size, 0, &data);
        memcpy(data, desc.data, (size_t)desc.data_size);
        vkUnmapMemory(*device_, memory_);
    }
}

VulkanBuffer::~VulkanBuffer() { vkDestroyBuffer(*device_, buffer_, nullptr); }
}
} // namespace tigine
