#include "vulkan/vulkan_render_target.h"

#include "vulkan/vulkan_texture.h"
#include "vulkan/vulkan_render_pass.h"

namespace tigine { namespace rhi {
VulkanRenderTarget::VulkanRenderTarget(const VulkanContextInfo &context, const RenderTargetDesc &desc) 
	: vk_device_(context.vk_device), resolution_(desc.resolution), samples_(desc.samples) {
	for (auto &texture : desc.target_textures) {
        if (texture.kind == RenderTargetTextureKind::Color) color_attachments_nums_++;
        if (texture.kind == RenderTargetTextureKind::Depth || texture.kind == RenderTargetTextureKind::DepthStencil)
            has_depth_attachment_ = true;
        if (texture.kind == RenderTargetTextureKind::Stencil || texture.kind == RenderTargetTextureKind::DepthStencil)
            has_stencil_attachment_ = true;
	}

    std::uint32_t num_attachments = desc.target_textures.size();
    std::vector<VkImageView> attachments(num_attachments);
    for (size_t i = 0; i < num_attachments; ++i) {
        VulkanTexture *vulkan_texture = dynamic_cast<VulkanTexture *>(desc.target_textures[i].texture);
        attachments[i]                = *vulkan_texture->getVKImageview();
    }

    VulkanRenderPass *vulkan_render_pass = dynamic_cast<VulkanRenderPass *>(desc.render_pass);

    VkFramebufferCreateInfo framebuffer_info {};
    framebuffer_info.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_info.renderPass      = *vulkan_render_pass->getVkRenderPass();
    framebuffer_info.attachmentCount = num_attachments;
    framebuffer_info.pAttachments    = attachments.data();
    framebuffer_info.width           = static_cast<uint32_t>(desc.resolution.width);
    framebuffer_info.height          = static_cast<uint32_t>(desc.resolution.height);
    framebuffer_info.layers          = 1;

    RHI_VULKAN_THROW_IF_FAILD(vkCreateFramebuffer(*vk_device_, &framebuffer_info, nullptr, &vk_frame_buffer_),
        "failed to create frame buffer!");
}
VulkanRenderTarget::~VulkanRenderTarget() {
    vkDestroyFramebuffer(*vk_device_, vk_frame_buffer_, nullptr);
}
}} // namespace tigine::rhi