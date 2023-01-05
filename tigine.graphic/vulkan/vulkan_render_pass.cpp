#include "vulkan/vulkan_render_pass.h"

namespace tigine { namespace graphic {
VulkanRenderPass::VulkanRenderPass(VkDevice *vk_device, const RenderPassDescriptor &desc) : vk_device_(vk_device) {

}

VulkanRenderPass::~VulkanRenderPass() { 
	vkDestroyRenderPass(*vk_device_, vk_render_pass_, nullptr);
}
}} // namespace tigine::graphic
