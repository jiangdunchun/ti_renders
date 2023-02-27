#include "vulkan/vulkan_render_pass.h"

#include <stdexcept>


namespace tigine { namespace graphic {
namespace {
VkAttachmentLoadOp mapAttachmentLoadOption(AttachmentLoadOption loadOp) {
    switch (loadOp) {
    case AttachmentLoadOption::Undefined:
        return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    case AttachmentLoadOption::Load:
        return VK_ATTACHMENT_LOAD_OP_LOAD;
    case AttachmentLoadOption::Clear:
        return VK_ATTACHMENT_LOAD_OP_CLEAR;
    }
    // @TODO
    return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
}
VkAttachmentStoreOp mapAttachmentStoreOption(AttachmentStoreOption storeOp) {
    switch (storeOp) {
    case AttachmentStoreOption::Undefined:
        return VK_ATTACHMENT_STORE_OP_DONT_CARE;
    case AttachmentStoreOption::Store:
        return VK_ATTACHMENT_STORE_OP_STORE;
    }
    // @TODO
    return VK_ATTACHMENT_STORE_OP_DONT_CARE;
}

VkFormat GetDepthStencilFormat(const DataFormat depthFormat, const DataFormat &stencilFormat) {
    if (depthFormat != DataFormat::Undefined && stencilFormat != DataFormat::Undefined) {
        if (depthFormat != stencilFormat) throw std::invalid_argument("format mismatch between depth and stencil render pass attachments");
        return mapVkFormat(depthFormat);
    }

    if (depthFormat != DataFormat::Undefined) {
        /* Get depth-stencil format from depth attachment only */
        return mapVkFormat(depthFormat);
    }

    if (stencilFormat != DataFormat::Undefined) {
        /* Get depth-stencil format from stencil attachment only */
        return mapVkFormat(stencilFormat);
    }
    //@TODO
    return VK_FORMAT_UNDEFINED;
}
}
VulkanRenderPass::VulkanRenderPass(VkDevice *vk_device, const RenderPassDescriptor &desc) : vk_device_(vk_device) {
    std::uint32_t numColorAttachments = static_cast<std::uint32_t>(desc.color_attachments.size());
    std::uint32_t numAttachments      = numColorAttachments;

    bool hasDepthStencil = false;
    if (desc.depth_attachment.format != DataFormat::Undefined || desc.stencil_attachment.format != DataFormat::Undefined) {
        ++numAttachments;
        hasDepthStencil = true;
    }

    std::vector<VkAttachmentDescription> attachmentDescs(desc.samples > 1 ? numAttachments + numColorAttachments : numAttachments);

    for (rsize_t i = 0; i < numColorAttachments; ++i) {
        attachmentDescs[i].flags          = 0;
        attachmentDescs[i].format         = mapVkFormat(desc.color_attachments[i].format);
        attachmentDescs[i].samples        = VK_SAMPLE_COUNT_1_BIT;
        attachmentDescs[i].loadOp         = mapAttachmentLoadOption(desc.color_attachments[i].load);
        attachmentDescs[i].storeOp        = mapAttachmentStoreOption(desc.color_attachments[i].store);
        attachmentDescs[i].stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachmentDescs[i].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachmentDescs[i].initialLayout  = (desc.color_attachments[i].load == AttachmentLoadOption::Load ? VK_IMAGE_LAYOUT_PRESENT_SRC_KHR : VK_IMAGE_LAYOUT_UNDEFINED);
        attachmentDescs[i].finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    }

    if (hasDepthStencil) {
        attachmentDescs[numColorAttachments].flags          = 0;
        attachmentDescs[numColorAttachments].format  = GetDepthStencilFormat(desc.depth_attachment.format, desc.stencil_attachment.format);
        attachmentDescs[numColorAttachments].samples        = VkSampleCountFlagBits(desc.samples);
        attachmentDescs[numColorAttachments].loadOp         = mapAttachmentLoadOption(desc.depth_attachment.load);
        attachmentDescs[numColorAttachments].storeOp        = mapAttachmentStoreOption(desc.depth_attachment.store);
        attachmentDescs[numColorAttachments].stencilLoadOp  = mapAttachmentLoadOption(desc.stencil_attachment.load);
        attachmentDescs[numColorAttachments].stencilStoreOp = mapAttachmentStoreOption(desc.stencil_attachment.store);
        attachmentDescs[numColorAttachments].initialLayout
            = desc.depth_attachment.load == AttachmentLoadOption::Load || desc.stencil_attachment.load == AttachmentLoadOption::Load ?
                   VK_IMAGE_LAYOUT_PRESENT_SRC_KHR :
                                                                                                          VK_IMAGE_LAYOUT_UNDEFINED;
        attachmentDescs[numColorAttachments].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    }

    //if (desc.samples > 1) {
    //    /* Take color attachment format descriptors for multi-sampled attachemnts */
    //    for (std::uint32_t i = 0; i < numColorAttachments; ++i)
    //        Convert(attachmentDescs[numAttachments + i], desc.colorAttachments[i], sampleCountBits);

    //    /* Modify original attachment descriptors */
    //    for (std::uint32_t i = 0; i < numColorAttachments; ++i)
    //        attachmentDescs[i].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    //}

    VkAttachmentDescription colorAttachment {};
    colorAttachment.format         = VK_FORMAT_R8G8B8A8_SRGB;
    colorAttachment.samples        = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef {};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass {};
    subpass.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments    = &colorAttachmentRef;

    VkSubpassDependency dependency {};
    dependency.srcSubpass    = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass    = 0;
    dependency.srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo renderPassInfo {};
    renderPassInfo.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments    = &colorAttachment;
    renderPassInfo.subpassCount    = 1;
    renderPassInfo.pSubpasses      = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies   = &dependency;

    if (vkCreateRenderPass(*vk_device_, &renderPassInfo, nullptr, vk_render_pass_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create render pass!");
    }
}

VulkanRenderPass::~VulkanRenderPass() { 
	vkDestroyRenderPass(*vk_device_, *vk_render_pass_, nullptr);
}
}} // namespace tigine::graphic
