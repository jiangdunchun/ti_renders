#ifndef TIGINE_GRAPHIC_GL430_GL430_RENDER_SYSTEM_H_
#define TIGINE_GRAPHIC_GL430_GL430_RENDER_SYSTEM_H_

#include "interface/i_render_system.h"

#include "gl430/gl430_buffer.h"
#include "gl430/gl430_buffer_array.h"
#include "gl430/gl430_command_buffer.h"
#include "gl430/gl430_command_queue.h"
#include "gl430/gl430_pipeline_state.h"
#include "gl430/gl430_render_context.h"
#include "gl430/gl430_shader.h"
#include "gl430/gl430_shader_program.h"

namespace tigine { namespace graphic {
class GL430RenderSystem : public IRenderSystem {
public:
    GL430RenderSystem() { command_queue_ = new GL430CommandQueue(); }
    ~GL430RenderSystem() { delete command_queue_; }
    DISALLOW_COPY_AND_ASSIGN(GL430RenderSystem);

    IRenderContext  *createRenderContext(const RenderContextDescriptor &desc) override { return new GL430RenderContext(desc); }
    void             release(IRenderContext *render_context) override { delete render_context; }
    IShader         *createShader(const ShaderDescriptor &desc) override { return new GL430Shader(desc); }
    void             release(IShader *shader) override { delete shader; }
    IShaderProgram  *createShaderProgram(const ShaderProgramDescriptor &desc) override { return new GL430ShaderProgram(desc); }
    void             release(IShaderProgram *shader_program) override { delete shader_program; }
    IBuffer         *createBuffer(const BufferDescriptor &desc, void *data) override { return new GL430Buffer(desc, data); }
    void             release(IBuffer *buffer) override { delete buffer; }
    IBufferArray    *createBufferArray(const BufferArrayDescriptor &desc) override { return new GL430BufferArray(desc); }
    void             release(IBufferArray *buffer_array) override { delete buffer_array; }
    ICommandQueue   *getCommandQueue() override { return command_queue_; }
    ICommandBuffer  *createCommandBuffer() override { return new GL430CommandBuffer(); }
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
    IPipelineState  *createPipelineState(const PipelineStateDescriptor &desc) override { return new GL430PipelineState(desc); }
    void             release(IPipelineState *pipeline) override { delete pipeline; }

private:
    GL430CommandQueue *command_queue_ = nullptr;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_GL430_GL430_RENDER_SYSTEM_H_
