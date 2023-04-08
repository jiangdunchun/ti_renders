#ifndef TIGINE_RHI_VULKAN_VULKAN_COMMON_H_
#define TIGINE_RHI_VULKAN_VULKAN_COMMON_H_

#include <vulkan/vulkan.h>
#include <glfw/glfw3.h>

#include "interface/i_common.h"

#define RHI_VULKAN_THROW(msg) RHI_THROW("vulkan " + std::string(msg))

#define RHI_VULKAN_THROW_IF_FAILD(result, msg) \
    if (result != VK_SUCCESS) RHI_VULKAN_THROW(msg)

namespace tigine { namespace rhi {
struct VulkanContextInfo {
    VkPhysicalDevice *vk_physical_device  = nullptr;
    VkDevice         *vk_device           = nullptr;
    VkQueue          *vk_graphics_queue   = nullptr;
    uint32_t          vk_graphics_family  = 0;
};


VkFormat mapVkFormat(DataFormat format);

void createVkBufferandDeviceMemory(VkPhysicalDevice     *physical_device,
                                   VkDevice             *device,
                                   VkDeviceSize          buffer_size,
                                   VkBufferUsageFlags    buffer_usage,
                                   VkMemoryPropertyFlags memory_property,
                                   VkBuffer             &o_buffer,
                                   VkDeviceMemory       &o_device_memory);

void createVkCommandPoolandCommandBuffers(VkDevice        *device,
                                          uint32_t         queue_family_index,
                                          uint32_t         num_buffers,
                                          VkCommandPool   &o_command_pool,
                                          VkCommandBuffer *o_command_buffers);
}}// namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_COMMON_H_
