#include "gl430plus_render_system.h"

#include "gl430plus_common.h"

namespace tigine {
	gl430plus_render_context* gl430plus_render_system::create_render_context(const render_context_descriptor& dscp) {
		gl430plus_render_context* render_cxt = new gl430plus_render_context(dscp);
		return render_cxt;
	}

	void gl430plus_render_system::release(gl430plus_render_context* render_cxt) {
		delete render_cxt;
		render_cxt = nullptr;
	}

	gl430plus_shader* gl430plus_render_system::create_shader(const shader_descriptor& desc) {
		gl430plus_shader* shader = new gl430plus_shader(desc);
		return shader;
	}

	void gl430plus_render_system::release(gl430plus_shader* render_cxt) {
	}

	gl430plus_shader_program* gl430plus_render_system::create_shader_program(const shader_program_descriptor& desc) {
		gl430plus_shader_program* shader_prog = new gl430plus_shader_program(desc);
		return shader_prog;
	}

	void gl430plus_render_system::release(gl430plus_shader_program* render_cxt) {
	}
}