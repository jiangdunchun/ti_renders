#ifndef TIGINE_RHI_VULKAN_VULKAN_COMMON_H_
#define TIGINE_RHI_VULKAN_VULKAN_COMMON_H_

#include <vulkan/vulkan.h>
#include <glfw/glfw3.h>

#include "interface/i_common.h"

namespace tigine { namespace rhi {
VkFormat mapVkFormat(DataFormat format);
}}// namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_COMMON_H_
