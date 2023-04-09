#include "vulkan/vulkan_render_target.h"

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

    // @TODO
}
}} // namespace tigine::rhi