#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_CONTEXT_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_CONTEXT_H_

#include "interface/i_render_context.h"

#include <string>
#include <vector>

#include "vulkan/vulkan_common.h"


namespace tigine { namespace graphic {
class VulkanSurface;
class VulkanRenderPass;
class VulkanRenderContext : public IRenderContext {
public:
    VulkanRenderContext(const RenderContextDescriptor &desc);
    ~VulkanRenderContext();

    IRenderPass *getRenderPass() override;
    ISurface    *getSurface() override;
    void         present() override;
    Extent2D     getResolution() override { return {600, 600}; }       //@TODO
    TUInt        getSamples() override { return 0; }                   // @TODO
    TUInt        getNumColorAttachments() const override { return 0; } // @TODO
    bool         hasDepthAttachment() const override { return 0; }     // @TODO
    bool         hasStencilAttachment() const override { return 0; }   // @TODO
    
    VkPhysicalDevice *getVkPhysicalDevice() { return &vk_physicl_device_; }
    VkDevice         *getVklDevice() { return &vk_device_; }

private:
    GLFWwindow       *window_;

    VulkanSurface    *surface_;
    VulkanRenderPass *render_pass_;

    VkInstance               vk_instance_;
    VkDebugUtilsMessengerEXT vk_debug_messenger_;
    VkSurfaceKHR             vk_surface_KHR_;
    VkPhysicalDevice         vk_physicl_device_;
    VkDevice                 vk_device_;
    VkQueue                  vk_graphics_queue_;
    VkQueue                  vk_present_queue_;
    VkSwapchainKHR           vk_swap_chain_;
    std::vector<VkImage>     vk_swap_chain_images_;
    VkFormat                 vk_swap_chain_image_format_;
    VkExtent2D               vk_swap_chain_extent_;
    std::vector<VkImageView> vk_swap_chain_image_views_;
    VkRenderPass             vk_render_pass_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_CONTEXT_H_