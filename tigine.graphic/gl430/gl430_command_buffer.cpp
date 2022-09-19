#include "gl430/gl430_command_buffer.h"

namespace tigine {
namespace graphic {
namespace {
GLbitfield mapClearFlags(std::uint8_t clear_flags) {
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

void GL430CommandBuffer::setViewport(const Viewport& viewport) {
	glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
}

void GL430CommandBuffer::setPipeState(GL430PipelineState* pipe_state) {
	glUseProgram(pipe_state->desc_.shader_program->getID());
	glClearColor(
		pipe_state->desc_.clear_value.color[0],
		pipe_state->desc_.clear_value.color[1],
		pipe_state->desc_.clear_value.color[2],
		pipe_state->desc_.clear_value.color[3]);
}

void GL430CommandBuffer::setVertexBufferArray(GL430BufferArray* buffer_array) {
	glBindVertexArray(buffer_array->getID());
}

void GL430CommandBuffer::beginRenderPass(GL430RenderPass* render_pass) {

}

void GL430CommandBuffer::endRenderPass() {

}

void GL430CommandBuffer::drawArray(std::uint32_t num_vertices, std::uint32_t first_vertex) {
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GL430CommandBuffer::clear(std::uint8_t clear_flags) {
	glClear(mapClearFlags(clear_flags));
}
} // namespace tigine::graphic
} // namespace tigine