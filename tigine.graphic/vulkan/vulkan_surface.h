#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_SURFACE_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_SURFACE_H_

#include "interface/i_surface.h"

#include "vulkan/vulkan_common.h"


namespace tigine { namespace graphic {
class VulkanSurface : public ISurface {
public:
    VulkanSurface(GLFWwindow *window);
    ~VulkanSurface();

    void setTitle(const std::string &name) override;
    void show() override;
    bool processEvents() override;

private:
    GLFWwindow *window_ = nullptr;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_SURFACE_H_
