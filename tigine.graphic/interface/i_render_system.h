#ifndef TIGINE_GRAPHIC_INTERFACE_I_RENDER_SYSTEM_H_
#define TIGINE_GRAPHIC_INTERFACE_I_RENDER_SYSTEM_H_

#include "interface/i_buffer.h"
#include "interface/i_buffer_array.h"
#include "interface/i_command_buffer.h"
#include "interface/i_command_queue.h"
#include "interface/i_common.h"
#include "interface/i_pipeline_layout.h"
#include "interface/i_pipeline_state.h"
#include "interface/i_render_context.h"
#include "interface/i_render_pass.h"
#include "interface/i_render_target.h"
#include "interface/i_resource_heap.h"
#include "interface/i_shader.h"
#include "interface/i_shader_program.h"
#include "interface/i_texture.h"

namespace tigine { namespace graphic {
class IRenderSystem : public NonCopyable {
public:
    virtual IRenderContext  *createRenderContext(const RenderContextDescriptor &desc)   = 0;
    virtual void             release(IRenderContext *render_context)                    = 0;
    virtual ICommandQueue   *getCommandQueue()                                          = 0;
    virtual ICommandBuffer  *createCommandBuffer()                                      = 0;
    virtual void             release(ICommandBuffer *command_buffer)                    = 0;
    virtual IBuffer         *createBuffer(const BufferDescriptor &desc, void *data)     = 0;
    virtual void             release(IBuffer *buffer)                                   = 0;
    virtual IBufferArray    *createBufferArray(const BufferArrayDescriptor &desc)       = 0;
    virtual void             release(IBufferArray *buffer_array)                        = 0;
    virtual IShader         *createShader(const ShaderDescriptor &desc)                 = 0;
    virtual void             release(IShader *shader)                                   = 0;
    virtual IShaderProgram  *createShaderProgram(const ShaderProgramDescriptor &desc)   = 0;
    virtual void             release(IShaderProgram *shader_program)                    = 0;
    virtual ITexture        *createTexture(const TextureDescriptor &desc)               = 0;
    virtual void             release(ITexture *texture)                                 = 0;
    virtual IResourceHeap   *CreateResourceHeap(const ResourceHeapDescriptor &desc)     = 0;
    virtual void             release(IResourceHeap *resource_heap)                      = 0;
    virtual IRenderPass     *CreateRenderPass(const RenderPassDescriptor &desc)         = 0;
    virtual void             release(IRenderPass *render_pass)                          = 0;
    virtual IRenderTarget   *createRenderTarget(const RenderTargetDescriptor &desc)     = 0;
    virtual void             release(IRenderTarget *render_target)                      = 0;
    virtual IPipelineLayout *createPipelineLayout(const PipelineLayoutDescriptor &desc) = 0;
    virtual void             release(IPipelineLayout *pipeline_layout)                  = 0;
    virtual IPipelineState  *createPipelineState(const PipelineStateDescriptor &desc)   = 0;
    virtual void             release(IPipelineState *pipeline_state)                    = 0;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_RENDER_SYSTEM_H_
