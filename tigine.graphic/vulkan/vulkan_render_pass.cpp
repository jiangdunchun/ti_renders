#include "vulkan/vulkan_render_pass.h"

namespace tigine { namespace graphic {
VulkanRenderPass::VulkanRenderPass(VkDevice *vk_device, const RenderPassDescriptor &desc) : vk_device_(vk_device) {

}

VulkanRenderPass::~VulkanRenderPass() {}
}} // namespace tigine::graphic
