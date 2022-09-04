#ifndef __I_SHADER_H__
#define __I_SHADER_H__

#include <glm/glm.hpp>

namespace tigine {
	struct shader_descriptor {
		glm::ivec2 resolution;
		unsigned int samples = 1;
		unsigned int color_bits = 32;
		unsigned int depth_bits = 24;
		unsigned int stencil_bits = 8;
		unsigned int stencil_bits = 8;
		unsigned int swapchain_size = 2;
	};

	class i_shader {

	};
}

#endif // !__I_SHADER_H__
