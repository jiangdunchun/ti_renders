#include "rhi.h"

#ifdef USING_VULKAN
#include "vulkan/vulkan_render_system.h"
#else
#include "gl430/gl430_render_system.h"
#endif

namespace tigine { namespace rhi {
#ifdef USING_VULKAN
IRenderSystem *CREATE_RENDER_SYSTEM() { return new VulkanRenderSystem(); }
#else
IRenderSystem *CREATE_RENDER_SYSTEM() { return new GL430RenderSystem(); }
#endif
}} // namespace tigine::rhi
