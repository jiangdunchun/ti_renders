#ifndef __I_RENDER_SYSTEM_H__
#define __I_RENDER_SYSTEM_H__

#include ¡°i_render_context.h¡±
#include "i_buffer.h"
#include "i_shader.h"
#include "i_shader_program.h"
#include "i_pipeline_state.h"
#include "i_command_queue.h"
#include "i_command_buffer.h"

namespace tigine {
	class i_render_system {
	public:
		virtual i_render_context* create_render_context(const render_context_descriptor& desc) = 0;
		virtual void release(i_render_context* render_ctx) = 0;

		virtual i_buffer* create_buffer(const buffer_descriptor& desc) = 0;
		virtual void release(i_buffer* buffer) = 0;

		virtual i_shader* create_shader(const shader_descriptor& desc) = 0;
		virtual void release(i_shader* shader) = 0;
		
		virtual i_shader_program* create_shader_program(const shader_program_descriptor& desc) = 0;
		virtual void release(i_shader_program* shader_pgm) = 0;

		virtual i_pipeline_state* create_pipeline_state(const pipeline_state_descriptor& desc) = 0;
		virtual void release(i_pipeline_state* pipeline_st) = 0;

		virtual i_command_queue* get_command_queue() {
			return m_command_queue;
		}

		virtual i_command_buffer* create_command_buffer() = 0;
		virtual void release(i_command_buffer* command_bf) = 0;

	protected:
		i_command_queue* m_command_queue;
	};
}

#endif // !__I_RENDER_H__
