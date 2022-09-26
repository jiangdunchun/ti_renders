#ifndef TIGINE_GRAPHIC_GRAPHIC_H_
#define TIGINE_GRAPHIC_GRAPHIC_H_

#ifdef USING_VULKAN
#include "vulkan/vulkan_render_system.h"
#define CREATE_RENDER_SYSTEM() new VulkanRenderSystem()
#else 
#include "gl430/gl430_render_system.h"
#define CREATE_RENDER_SYSTEM() new GL430RenderSystem()
#endif


#endif // !TIGINE_GRAPHIC_GRAPHIC_H_
