#ifndef __I_RENDER_CONTEXT_H__
#define __I_RENDER_CONTEXT_H__

#include <glm/glm.hpp>

namespace tigine {
	struct render_context_descriptor {
		glm::ivec2 resolution;
		unsigned int samples = 1;
		unsigned int color_bits = 32;
		unsigned int depth_bits = 24;
		unsigned int stencil_bits = 8;
		unsigned int stencil_bits = 8;
		unsigned int swapchain_size = 2;
	};

	class i_render_context {
	protected:
		render_context_descriptor m_ctx_desc;
	public:
		explicit i_render_context(const render_context_descriptor& ctx_desc) : m_ctx_desc(ctx_desc) {}
		virtual i_render_context() {}

		glm::ivec2 get_resolution() const {
			return m_ctx_desc.resolution;
		}
		virtual void present() = 0;
	};
}

#endif // !__I_RENDER_CONTEXT_H__
