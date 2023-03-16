#ifndef TIGINE_RHI_VULKAN_VULKAN_COMMON_H_
#define TIGINE_RHI_VULKAN_VULKAN_COMMON_H_

#include <vulkan/vulkan.h>
#include <glfw/glfw3.h>

#include "interface/i_common.h"

#define RHI_VULKAN_THROW(msg) RHI_THROW("vulkan " + std::string(msg))

#define RHI_VULKAN_THROW_IF_FAILD(result, msg) \
    if (result != VK_SUCCESS) RHI_VULKAN_THROW(msg)

namespace tigine { namespace rhi {
VkFormat mapVkFormat(DataFormat format);

void createVkBuffer(VkPhysicalDevice     *physical_divece,
                    VkDevice             *device,
                    VkDeviceSize          size,
                    VkBufferUsageFlags    usage,
                    VkMemoryPropertyFlags properties,
                    VkBuffer             &o_buffer,
                    VkDeviceMemory       &o_memory);
}}// namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_COMMON_H_
