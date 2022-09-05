#ifndef __GL430PLUS_RENDER_CONTEXT_H__
#define __GL430PLUS_RENDER_CONTEXT_H__

#include <cstdint>

#include "gl430plus_surface.h"

namespace tigine {
	struct render_context_descriptor {
		std::uint32_t width;
		std::uint32_t height;
		std::uint32_t samples = 1;
	};

	class gl430plus_render_system;
	class gl430plus_render_context {
		friend class gl430plus_render_system;
	private:
		render_context_descriptor m_desc;
		gl430plus_surface m_surface;

		gl430plus_render_context(const render_context_descriptor& desc);
		~gl430plus_render_context();
		
	public:
		gl430plus_surface* get_surface() {
			return &m_surface;
		}
	};
}

#endif // !__GL430PLUS_RENDER_CONTEXT_H__