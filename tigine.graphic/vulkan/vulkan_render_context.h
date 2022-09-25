#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_CONTEXT_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_CONTEXT_H_

#include <string>

#include "vulkan/vulkan_common.h"
#include "vulkan/vulkan_surface.h"
#include "interface/i_render_context.h"

namespace tigine { namespace graphic {
class VulkanRenderContext : public IRenderContext {
public:
    VulkanRenderContext(const RenderContextDescriptor &desc);
    ~VulkanRenderContext();
    DISALLOW_COPY_AND_ASSIGN(VulkanRenderContext);

    Viewport getResolution() override { return {600, 600}; }
    void     present() override { glfwSwapBuffers(static_cast<VulkanSurface *>(surface_)->window_); }
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_CONTEXT_H_