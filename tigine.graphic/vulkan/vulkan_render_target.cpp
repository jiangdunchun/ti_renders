#include "vulkan/vulkan_render_target.h"

namespace tigine { namespace graphic {
VulkanRenderTarget::VulkanRenderTarget(VkDevice *vk_device, const RenderTargetDesc &desc) 
	: resolution_(desc.resolution), samples_(desc.samples) {
	for (auto &attachment : desc.attachments) {
        if (attachment.kind == AttachmentKind::Color) color_attachments_nums_++;
        if (attachment.kind == AttachmentKind::Depth || attachment.kind == AttachmentKind::DepthStencil) has_depth_attachment_ = true;
        if (attachment.kind == AttachmentKind::Stencil || attachment.kind == AttachmentKind::DepthStencil) has_stencil_attachment_ = true;
	}
}
}} // namespace tigine::graphic