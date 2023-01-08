#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_BUFFER_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_BUFFER_H_

#include "interface/i_command_buffer.h"

#include "vulkan/vulkan_common.h"


namespace tigine { namespace graphic {
class VulkanCommandBuffer : public ICommandBuffer {
public:
    VulkanCommandBuffer(VkDevice *vk_device, const CommandBufferDescriptor &desc);
    ~VulkanCommandBuffer();

    void begin() override;
    void end() override;
    void setViewport(const Viewport &viewport) override;
    void setPipeState(IPipelineState *pipe_state) override;
    void setVertexBufferArray(IBufferArray *buffer_array) override;
    void beginRenderPass(IRenderPass *render_pass) override;
    void endRenderPass() override;
    void drawArray(TULong num_vertices, TULong first_vertex) override;
    void clear(TChar clear_flags) override;

private:
    VkDevice *vk_device_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_BUFFER_H_
