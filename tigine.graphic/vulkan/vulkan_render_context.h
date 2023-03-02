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
    VulkanRenderContext(const RenderContextDesc &desc);
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
    VkQueue          *getVkGraphicsQueue() { return &vk_graphics_queue_; }
    uint32_t          getVkGraphicsFamily() { return vk_graphics_family_; }
    VkFramebuffer    *getVkFrameBuffer() { return &vk_swapchain_frame_buffers_[present_image_index_]; }

private:
    void acquireNextPresentImage();

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
    uint32_t                 vk_graphics_family_;

    VkSwapchainKHR             vk_swapchain_;
    VkFormat                   vk_swapchain_image_format_;
    VkExtent2D                 vk_swapchain_extent_;
    std::vector<VkImage>       vk_swapchain_images_;
    std::vector<VkImageView>   vk_swapchain_image_views_;
    std::vector<VkFramebuffer> vk_swapchain_frame_buffers_;

    
    VkSemaphore vk_image_available_semaphore_;
    VkSemaphore vk_render_finished_semaphore_;
    TUInt       present_image_index_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_CONTEXT_H_