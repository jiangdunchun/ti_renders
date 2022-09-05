#ifndef __GL430PLUS_RENDER_SYSTEM_H__
#define __GL430PLUS_RENDER_SYSTEM_H__

#include "gl430plus_render_context.h"
#include "gl430plus_shader.h"
#include "gl430plus_shader_program.h"

namespace tigine {
	class gl430plus_render_system {
	public:
		gl430plus_render_context* create_render_context(const render_context_descriptor& desc);
		void release(gl430plus_render_context* render_cxt);

		gl430plus_shader* create_shader(const shader_descriptor& desc);
		void release(gl430plus_shader* render_cxt);

		gl430plus_shader_program* create_shader_program(const shader_program_descriptor& desc);
		void release(gl430plus_shader_program* render_cxt);
	};
}

#endif // !__GL430PLUS_RENDER_SYSTEM.H__
