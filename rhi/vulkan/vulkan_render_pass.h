#ifndef TIGINE_RHI_VULKAN_VULKAN_RENDER_PASS_H_
#define TIGINE_RHI_VULKAN_VULKAN_RENDER_PASS_H_

#include "interface/i_render_pass.h"

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanRenderPass : public IRenderPass {
public:
    VulkanRenderPass(const VulkanContextInfo &context, const RenderPassDesc &desc);
    ~VulkanRenderPass();

    VkRenderPass *getVkRenderPass() { return &vk_render_pass_; }

private:
    VkDevice *vk_device_;

    VkRenderPass vk_render_pass_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_RENDER_PASS_H_
