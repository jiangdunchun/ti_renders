#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_SYSTEM_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_SYSTEM_H_

#include "interface/i_render_system.h"

#include "vulkan/vulkan_buffer.h"
#include "vulkan/vulkan_buffer_array.h"
#include "vulkan/vulkan_command_buffer.h"
#include "vulkan/vulkan_command_queue.h"
#include "vulkan/vulkan_pipeline_state.h"
#include "vulkan/vulkan_render_context.h"
#include "vulkan/vulkan_shader.h"
#include "vulkan/vulkan_shader_program.h"

namespace tigine { namespace graphic {
class VulkanRenderSystem : public IRenderSystem {
public:
    VulkanRenderSystem() { command_queue_ = new VulkanCommandQueue(); }
    ~VulkanRenderSystem() { delete command_queue_; }
    DISALLOW_COPY_AND_ASSIGN(VulkanRenderSystem);

    IRenderContext  *createRenderContext(const RenderContextDescriptor &desc) override { return new VulkanRenderContext(desc); }
    void             release(IRenderContext *render_context) override { delete render_context; }
    IShader         *createShader(const ShaderDescriptor &desc) override { return new VulkanShader(desc); }
    void             release(IShader *shader) override { delete shader; }
    IShaderProgram  *createShaderProgram(const ShaderProgramDescriptor &desc) override { return new VulkanShaderProgram(desc); }
    void             release(IShaderProgram *shader_program) override { delete shader_program; }
    IBuffer         *createBuffer(const BufferDescriptor &desc, void *data) override { return new VulkanBuffer(desc, data); }
    void             release(IBuffer *buffer) override { delete buffer; }
    IBufferArray    *createBufferArray(const BufferArrayDescriptor &desc) override { return new VulkanBufferArray(desc); }
    void             release(IBufferArray *buffer_array) override { delete buffer_array; }
    ICommandQueue   *getCommandQueue() override { return command_queue_; }
    ICommandBuffer  *createCommandBuffer() override { return new VulkanCommandBuffer(); }
    void             release(ICommandBuffer *command_buffer) override { delete command_buffer; }
    ITexture        *createTexture(const TextureDescriptor &desc) override { return nullptr; }
    void             release(ITexture *render_target) override {}
    ISampler        *CreateSampler(const SamplerDescriptor &desc) { return nullptr; }
    void             release(ISampler *sampler) {}
    IResourceHeap   *CreateResourceHeap(const ResourceHeapDescriptor &desc) { return nullptr; }
    void             release(IResourceHeap *resource_heap) {}
    IRenderPass     *CreateRenderPass(const RenderPassDescriptor &desc) { return nullptr; }
    void             release(IRenderPass *render_pass) {}
    IRenderTarget   *createRenderTarget(const RenderTargetDescriptor &desc) override { return nullptr; }
    void             release(IRenderTarget *render_target) override {}
    IPipelineLayout *createPipelineLayout(const PipelineLayoutDescriptor &desc) override { return nullptr; }
    void             release(IPipelineLayout *pipeline_layout) override {}
    IPipelineState  *createPipelineState(const PipelineStateDescriptor &desc) override { return new VulkanPipelineState(desc); }
    void             release(IPipelineState *pipeline) override { delete pipeline; }

private:
    VulkanCommandQueue *command_queue_ = nullptr;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_SYSTEM_H_
