#ifndef TIGINE_GRAPHIC_INTERFACE_I_RENDER_SYSTEM_H_
#define TIGINE_GRAPHIC_INTERFACE_I_RENDER_SYSTEM_H_

#include "interface/i_buffer.h"
#include "interface/i_buffer_array.h"
#include "interface/i_command_buffer.h"
#include "interface/i_command_queue.h"
#include "interface/i_common.h"
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
    virtual IRenderContext  *createRenderContext(const RenderContextDesc &desc)   = 0;
    virtual ICommandQueue   *getCommandQueue()                                          = 0;
    virtual ICommandBuffer  *createCommandBuffer(const CommandBufferDesc &desc)   = 0;
    virtual IBuffer         *createBuffer(const BufferDesc &desc)                 = 0;
    virtual IBufferArray    *createBufferArray(const BufferArrayDesc &desc)       = 0;
    virtual IShader         *createShader(const ShaderDesc &desc)                 = 0;
    virtual IShaderProgram  *createShaderProgram(const ShaderProgramDesc &desc)   = 0;
    virtual ITexture        *createTexture(const TextureDesc &desc)               = 0;
    virtual IResourceHeap   *CreateResourceHeap(const ResourceHeapDesc &desc)     = 0;
    virtual IRenderPass     *CreateRenderPass(const RenderPassDesc &desc)         = 0;
    virtual IRenderTarget   *createRenderTarget(const RenderTargetDesc &desc)     = 0;
    virtual IPipelineState  *createPipelineState(const PipelineStateDesc &desc)   = 0;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_RENDER_SYSTEM_H_
