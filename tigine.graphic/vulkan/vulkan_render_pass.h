#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_PASS_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_PASS_H_

#include "interface/i_render_pass.h"

#include "vulkan/vulkan_common.h"


namespace tigine { namespace graphic {
class VulkanRenderContext;
class VulkanRenderPass : public IRenderPass {
    friend class VulkanRenderContext;

public:
    VulkanRenderPass(VkDevice *vk_device, const RenderPassDesc &desc);
    ~VulkanRenderPass();

    VkRenderPass *getVkRenderPass() { return &vk_render_pass_; }

private:
    VulkanRenderPass(VkDevice *vk_device) : vk_device_(vk_device) {}

    VkDevice *vk_device_;

    VkRenderPass vk_render_pass_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_PASS_H_
