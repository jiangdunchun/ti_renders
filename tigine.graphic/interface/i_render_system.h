#ifndef TIGINE_GRAPHIC_INTERFACE_I_RENDER_SYSTEM_H_
#define TIGINE_GRAPHIC_INTERFACE_I_RENDER_SYSTEM_H_

#include "interface/i_common.h"
#include "interface/i_render_context.h"
#include "interface/i_shader.h"
#include "interface/i_shader_program.h"
#include "interface/i_buffer.h"
#include "interface/i_buffer_array.h"
#include "interface/i_command_queue.h"
#include "interface/i_command_buffer.h"
#include "interface/i_pipeline_state.h"

namespace tigine { namespace graphic {
class IRenderSystem {
public:
    virtual IRenderContext*     createRenderContext(const RenderContextDescriptor& desc) = 0;
    virtual void            release(IRenderContext* render_context)                  = 0;
    virtual IShader*            createShader(const ShaderDescriptor& desc)               = 0;
    virtual void                release(IShader* shader)                                 = 0;
    virtual IShaderProgram*     createShaderProgram(const ShaderProgramDescriptor& desc) = 0;
    virtual void                release(IShaderProgram* shader_program)                  = 0;
    virtual IBuffer*               createBuffer(const BufferDescriptor& desc, void* data)   = 0;
    virtual void                release(IBuffer* buffer)                                 = 0;
    virtual IBufferArray*          createBufferArray(const BufferArrayDescriptor& desc)     = 0;
    virtual void                   release(IBufferArray* buffer_array)                      = 0;
    virtual ICommandQueue*         getCommandQueue()                                        = 0;
    virtual ICommandBuffer*        createCommandBuffer()                                    = 0;
    virtual void                   release(ICommandBuffer* command_buffer)                  = 0;
    virtual IPipelineState*        createPipeline(const PipelineStateDescriptor& desc)      = 0;
    virtual void                   release(IPipelineState* pipeline)                        = 0;
};
}} // // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_RENDER_SYSTEM_H_
