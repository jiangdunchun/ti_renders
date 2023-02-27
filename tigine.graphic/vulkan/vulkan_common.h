#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_COMMON_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_COMMON_H_

#include <vulkan/vulkan.h>
#include <glfw/glfw3.h>

#include "interface/i_common.h"

namespace tigine { namespace graphic {
VkFormat mapVkFormat(DataFormat format);
}}// namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_COMMON_H_
