#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_TARGET_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_TARGET_H_

#include "interface/i_render_target.h"

#include "vulkan/vulkan_common.h"

namespace tigine { namespace graphic {
class VulkanRenderTarget : public IRenderTarget {
public:
    VulkanRenderTarget(VkDevice *vk_device, const RenderTargetDescriptor &desc);
    ~VulkanRenderTarget() {}

    virtual IRenderPass *getRenderPass() override { return nullptr; }
    virtual Extent2D     getResolution() override { return resolution_; }
    virtual TUInt        getSamples() override { return samples_; }
    virtual TUInt        getNumColorAttachments() const override { return color_attachments_nums_; }
    virtual bool         hasDepthAttachment() const override { return has_depth_attachment_; }
    virtual bool         hasStencilAttachment() const override { return has_stencil_attachment_; }

private:
    VkDevice *vk_device_;

    Extent2D resolution_;
    TUInt    samples_;
    TUInt    color_attachments_nums_ = 0;
    bool    has_depth_attachment_    = false;
    bool    has_stencil_attachment_  = false;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_TARGET_H_