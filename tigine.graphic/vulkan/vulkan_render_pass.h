#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_PASS_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_PASS_H_

#include "vulkan/vulkan_common.h"
#include "interface/i_render_pass.h"

namespace tigine { namespace graphic {
class VulkanRenderPass : public IRenderPass {
public:
    VulkanRenderPass(const RenderPassDescriptor &desc) {}
    ~VulkanRenderPass() = default;
    DISALLOW_COPY_AND_ASSIGN(VulkanRenderPass);

private:
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_PASS_H_
