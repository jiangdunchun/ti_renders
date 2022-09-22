#include "gl430/gl430_command_buffer.h"

#include "gl430/gl430_buffer_array.h"
#include "gl430/gl430_pipeline_state.h"
#include "gl430/gl430_render_pass.h"
#include "gl430/gl430_shader_program.h"

namespace tigine { namespace graphic {
namespace {
GLbitfield mapClearFlags(TChar clear_flags) {
    GLbitfield ret = 0;
    if (clear_flags & CF_Color) ret |= GL_COLOR;
    if (clear_flags & CF_Depth) ret |= GL_DEPTH;
    if (clear_flags & CF_Stencil) ret |= GL_STENCIL;
    return ret;
}
} // namespace

GL430CommandBuffer::GL430CommandBuffer() {}

GL430CommandBuffer::~GL430CommandBuffer() {}

void GL430CommandBuffer::begin() {}

void GL430CommandBuffer::end() {}

void GL430CommandBuffer::setViewport(const Viewport &viewport) { glViewport(viewport.x, viewport.y, viewport.width, viewport.height); }

void GL430CommandBuffer::setPipeState(IPipelineState *pipe_state) {
    glUseProgram(static_cast<GL430ShaderProgram *>(pipe_state->getShaderProgram())->getID());
    glClearColor(pipe_state->getClearValue().color[0],
                 pipe_state->getClearValue().color[1],
                 pipe_state->getClearValue().color[2],
                 pipe_state->getClearValue().color[3]);
}

void GL430CommandBuffer::setVertexBufferArray(IBufferArray *buffer_array) {
    glBindVertexArray(static_cast<GL430BufferArray *>(buffer_array)->getID());
}

void GL430CommandBuffer::beginRenderPass(IRenderPass *render_pass) {}

void GL430CommandBuffer::endRenderPass() {}

void GL430CommandBuffer::drawArray(TULong num_vertices, TULong first_vertex) { glDrawArrays(GL_TRIANGLES, 0, 3); }

void GL430CommandBuffer::clear(TChar clear_flags) { glClear(mapClearFlags(clear_flags)); }
}} // namespace tigine::graphic