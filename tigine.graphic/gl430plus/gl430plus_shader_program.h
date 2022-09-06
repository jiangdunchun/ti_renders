#ifndef __GL430PLUS_SHADER_PROGRAM_H__
#define __GL430PLUS_SHADER_PROGRAM_H__

#include "gl430plus_shader.h"

namespace tigine {
	struct shader_program_descriptor {
		gl430plus_shader* vertex_shader = nullptr;
		gl430plus_shader* fragment_shader = nullptr;
		gl430plus_shader* compute_shader = nullptr;
	};

	class gl430plus_shader_program {
	private:
		GLuint m_id;
		GLuint m_log_len = 0;

	public:
		gl430plus_shader_program(const shader_program_descriptor& desc);
		~gl430plus_shader_program();
		bool has_error() const;
		std::string get_report() const;
	};
}

#endif // !__GL430PLUS_SHADER_PROGRAM_H__
