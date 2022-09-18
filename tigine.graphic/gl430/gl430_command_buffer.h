#ifndef TIGINE_GRAPHIC_GL430_GL430_COMMAND_BUFFER_H_
#define TIGINE_GRAPHIC_GL430_GL430_COMMAND_BUFFER_H_

#include <cstdint>

#include "gl430/gl430_common.h"
#include "gl430/gl430_pipeline_state.h"
#include "gl430/gl430_buffer_array.h"

namespace tigine {
namespace graphic {
class GL430CommandBuffer {
public:
    GL430CommandBuffer() = default;
    ~GL430CommandBuffer() = default;
    DISALLOW_COPY_AND_ASSIGN(GL430CommandBuffer);

    void begin();
    void end();
    void setViewport(const Viewport& viewport);
    void setPipeState(GL430PipelineState* pipe_state);
    void setVertexBufferArray(GL430BufferArray* buffer_array);
    void beginRenderPass(GL430RenderPass* render_pass);
    void endRenderPass();
    void drawArray(std::uint32_t num_vertices, std::uint32_t first_vertex);
    void clear(std::uint8_t clear_flags);
};
} // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_GL430_GL430_COMMAND_BUFFER_H_
