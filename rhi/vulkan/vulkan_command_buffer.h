#ifndef TIGINE_RHI_VULKAN_VULKAN_COMMAND_BUFFER_H_
#define TIGINE_RHI_VULKAN_VULKAN_COMMAND_BUFFER_H_

#include "interface/i_command_buffer.h"

#include <vector>

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanCommandBuffer : public ICommandBuffer {
public:
    VulkanCommandBuffer(const VulkanContextInfo &context, const CommandBufferDesc &desc);
    ~VulkanCommandBuffer();

    void begin() override;
    void end() override;
    void setViewport(const Viewport &viewport) override;
    void setPipeState(IPipelineState *pipe_state) override;
    void setVertexBufferArray(IBufferArray *buffer_array) override;
    void beginRenderPass(IRenderTarget *render_target) override;
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
    bool                         draw_indexed_ = false;

};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_COMMAND_BUFFER_H_
