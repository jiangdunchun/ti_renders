#ifndef TIGINE_GRAPHIC_INTERFACE_I_COMMAND_BUFFER_H_
#define TIGINE_GRAPHIC_INTERFACE_I_COMMAND_BUFFER_H_

#include "interface/i_buffer_array.h"
#include "interface/i_common.h"
#include "interface/i_pipeline_state.h"
#include "interface/i_render_pass.h"

namespace tigine { namespace graphic {
class IRenderTarget;

struct CommandBufferDescriptor {
    TUInt buffer_size = 2;
};

class ICommandBuffer : public NonCopyable {
public:
    virtual void begin()                                             = 0;
    virtual void end()                                               = 0;
    virtual void setViewport(const Viewport &viewport)               = 0;
    virtual void setPipeState(IPipelineState *pipe_state)            = 0;
    virtual void setVertexBufferArray(IBufferArray *buffer_array)    = 0;
    virtual void beginRenderPass(IRenderTarget *render_target, IRenderPass *render_pass) = 0;
    virtual void endRenderPass()                                     = 0;
    virtual void drawArray(TULong num_vertices, TULong first_vertex) = 0;
    virtual void clear(TChar clear_flags)                            = 0;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_COMMAND_BUFFER_H_
