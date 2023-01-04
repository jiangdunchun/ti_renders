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
    virtual IRenderContext  *createRenderContext(const RenderContextDescriptor &desc)   = 0;
    virtual ICommandQueue   *getCommandQueue()                                          = 0;
    virtual ICommandBuffer  *createCommandBuffer()                                      = 0;
    virtual IBuffer         *createBuffer(const BufferDescriptor &desc)                 = 0;
    virtual IBufferArray    *createBufferArray(const BufferArrayDescriptor &desc)       = 0;
    virtual IShader         *createShader(const ShaderDescriptor &desc)                 = 0;
    virtual IShaderProgram  *createShaderProgram(const ShaderProgramDescriptor &desc)   = 0;
    virtual ITexture        *createTexture(const TextureDescriptor &desc)               = 0;
    virtual IResourceHeap   *CreateResourceHeap(const ResourceHeapDescriptor &desc)     = 0;
    virtual IRenderPass     *CreateRenderPass(const RenderPassDescriptor &desc)         = 0;
    virtual IRenderTarget   *createRenderTarget(const RenderTargetDescriptor &desc)     = 0;
    virtual IPipelineState  *createPipelineState(const PipelineStateDescriptor &desc)   = 0;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_RENDER_SYSTEM_H_
