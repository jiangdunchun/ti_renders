#ifndef TIGINE_RHI_INTERFACE_I_COMMAND_BUFFER_H_
#define TIGINE_RHI_INTERFACE_I_COMMAND_BUFFER_H_

#include "interface/i_buffer_array.h"
#include "interface/i_common.h"
#include "interface/i_pipeline_state.h"
#include "interface/i_render_target.h"

namespace tigine { namespace rhi {
enum ClearFlag : TChar {
    CF_Color = 1 << 0,
    CF_Depth = 1 << 1,
    CF_Stencil = 1 << 2
};

struct Viewport {
    TUInt x;
    TUInt y;
    TUInt width;
    TUInt height;
};

struct CommandBufferDesc {
};

class ICommandBuffer : public NonCopyable {
public:
    virtual ~ICommandBuffer() = default;

    virtual void begin()                                             = 0;
    virtual void end()                                               = 0;
    virtual void setViewport(const Viewport &viewport)               = 0;
    virtual void setPipeState(IPipelineState *pipe_state)            = 0;
    virtual void setVertexBufferArray(IBufferArray *buffer_array)    = 0;
    virtual void beginRenderPass(IRenderTarget *render_target)       = 0;
    virtual void endRenderPass()                                     = 0;
    virtual void drawArray(TULong num_vertices, TULong first_vertex) = 0;
    virtual void clear(TChar clear_flags)                            = 0;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_COMMAND_BUFFER_H_
