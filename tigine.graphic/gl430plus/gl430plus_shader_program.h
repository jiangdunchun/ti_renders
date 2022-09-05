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
	};
}

#endif // !__GL430PLUS_SHADER_PROGRAM_H__
