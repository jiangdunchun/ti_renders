#ifndef TIGINE_RHI_GL430_GL430_COMMAND_BUFFER_H_
#define TIGINE_RHI_GL430_GL430_COMMAND_BUFFER_H_

#include "gl430/gl430_common.h"
#include "interface/i_command_buffer.h"

namespace tigine { namespace rhi {
class GL430CommandBuffer : public ICommandBuffer {
public:
    GL430CommandBuffer();
    ~GL430CommandBuffer();

    void begin() override;
    void end() override;
    void setViewport(const Viewport &viewport) override;
    void setPipeState(IPipelineState *pipe_state) override;
    void setVertexBufferArray(IBufferArray *buffer_array) override;
    void beginRenderPass(IRenderPass *render_pass) override;
    void endRenderPass() override;
    void drawArray(TULong num_vertices, TULong first_vertex) override;
    void clear(TChar clear_flags) override;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_GL430_GL430_COMMAND_BUFFER_H_
