#include "vulkan/vulkan_render_context.h"

namespace tigine { namespace graphic {
VulkanRenderContext::VulkanRenderContext(const RenderContextDescriptor &desc) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window_ = glfwCreateWindow(desc.width, desc.height, "", NULL, NULL);
    if (!window_) {
        // @TODO
        glfwTerminate();
    }

    glfwMakeContextCurrent(window_);

    surface_     = new VulkanSurface(window_);
    render_pass_ = nullptr;
}

VulkanRenderContext::~VulkanRenderContext() {
    if (window_) glfwDestroyWindow(window_);
    delete surface_;
    delete render_pass_;
    glfwTerminate();
}
}} // namespace tigine::graphic
