#ifndef TIGINE_GRAPHIC_GRAPHIC_H_
#define TIGINE_GRAPHIC_GRAPHIC_H_

#include "gl430/gl430_render_system.h"
#include "gl430/gl430_surface.h"
#include "gl430/gl430_render_context.h"
#include "gl430/gl430_shader.h"
#include "gl430/gl430_shader_program.h"
#include "gl430/gl430_buffer.h"
#include "gl430/gl430_buffer_array.h"
#include "gl430/gl430_command_buffer.h"
#include "gl430/gl430_command_queue.h"
#include "gl430/gl430_render_pass.h"
#include "gl430/gl430_pipeline_state.h"

namespace tigine {
namespace graphic {
#if 1
typedef GL430RenderSystem	RenderSystem;
typedef GL430Surface		Surface;
typedef GL430RenderContext	RenderContext;
typedef GL430Shader			Shader;
typedef GL430ShaderProgram  ShaderProgram;
typedef GL430Buffer  Buffer;
typedef GL430BufferArray  BufferArray;
typedef GL430CommandBuffer  CommandBuffer;
typedef GL430CommandQueue	CommandQueue;
typedef GL430RenderPass		RenderPass;
typedef GL430PipelineState	PipelineState;
#else

#endif
} // namespace tigine::graphic
} // namespace tigine


#endif // !TIGINE_GRAPHIC_GRAPHIC_H_
