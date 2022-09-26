#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_SURFACE_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_SURFACE_H_

#include "vulkan/vulkan_common.h"

#include "interface/i_surface.h"

namespace tigine { namespace graphic {
class VulkanRenderContext;
class VulkanSurface : public ISurface {
public:
    VulkanSurface()  = default;
    ~VulkanSurface() = default;

    void setTitle(const std::string &name) override { glfwSetWindowTitle(window_, name.c_str()); }
    void show() override { glfwShowWindow(window_); }
    bool processEvents() override {
        glfwPollEvents();
        return !glfwWindowShouldClose(window_);
    }

private:
    friend class VulkanRenderContext;
    GLFWwindow *window_ = nullptr;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_SURFACE_H_
