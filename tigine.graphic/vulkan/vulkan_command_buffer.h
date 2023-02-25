#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_BUFFER_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_BUFFER_H_

#include "interface/i_command_buffer.h"

#include "vulkan/vulkan_common.h"

#include <vector>


namespace tigine { namespace graphic {
class VulkanCommandBuffer : public ICommandBuffer {
public:
    VulkanCommandBuffer(VkDevice *vk_device, VkQueue *graphics_queue, uint32_t queue_family_index, const CommandBufferDescriptor &desc);
    ~VulkanCommandBuffer();

    void begin() override;
    void end() override;
    void setViewport(const Viewport &viewport) override;
    void setPipeState(IPipelineState *pipe_state) override;
    void setVertexBufferArray(IBufferArray *buffer_array) override;
    void beginRenderPass(IRenderTarget *render_target, IRenderPass *render_pass) override;
    void endRenderPass() override;
    void drawArray(TULong num_vertices, TULong first_vertex) override;
    void clear(TChar clear_flags) override;

    VkCommandBuffer *getVKCommandBuffer() { return &vk_command_buffer_; }
    VkFence         *getVKQueueSubmitFence() { return &vk_queue_submit_fence_; }

private:
    VkDevice      *vk_device_;
    
    VkCommandPool                vk_command_pool_;
    std::vector<VkCommandBuffer> vk_command_buffers_;
    std::vector<VkFence>         vk_recording_fences_;

    bool                  vk_draw_indexed_ = false;
    VkCommandBuffer       vk_command_buffer_;
    VkRenderPassBeginInfo vk_render_pass_info_;
    VkFence               vk_queue_submit_fence_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_BUFFER_H_
