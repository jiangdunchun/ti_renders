#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_BUFFER_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_BUFFER_H_

#include "interface/i_command_buffer.h"

#include "vulkan/vulkan_common.h"

#include <vector>


namespace tigine { namespace graphic {
class VulkanCommandBuffer : public ICommandBuffer {
public:
    VulkanCommandBuffer(VkDevice *vk_device, VkQueue *vk_graphics_queue, uint32_t vk_queue_family_index, const CommandBufferDescriptor &desc);
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

    VkCommandBuffer *getVKCommandBuffer() { return vk_now_command_buffer_; }
    VkFence         *getVKQueueSubmitFence() { return vk_now_fence_; }

private:
    void acquireNextBuffer();

private:
    VkDevice      *vk_device_;
    
    VkCommandPool                vk_command_pool_;
    std::vector<VkCommandBuffer> vk_command_buffers_;
    std::vector<VkFence>         vk_fences_;
    VkRenderPassBeginInfo        vk_render_pass_info_;
    TUInt                        buffers_count_;
    TUInt                        buffers_next_index_ = 0;
    VkCommandBuffer             *vk_now_command_buffer_;
    VkFence                     *vk_now_fence_;
    bool                         vk_draw_indexed_ = false;

};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_COMMAND_BUFFER_H_
