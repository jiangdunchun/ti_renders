#ifndef __GL3PLUS_RENDER_SYSTEM_H__
#define __GL3PLUS_RENDER_SYSTEM_H__

#include <string>

#include "gl3plus_common.h"

namespace ti_render {
	class gl3plus_render_system {
	private:
		GLFWwindow* m_window;

	public:
		bool init(unsigned int width, unsigned int height, const std::string& name);
		void shutdown(void);
		bool is_active(void);
		void set_clear_color(const glm::vec4& color);
		void set_resolution(unsigned int width, unsigned int height);
		void clear_frame_buffer(char mask);
		void enable(graphic_capability capability);
		void disable(graphic_capability capability);
		void set_depth_func(depth_func func);
		void pre_rend_one_frame(void);
		void post_rend_one_frame(void);
	};
}

#endif // !__GL3PLUS_RENDER_SYSTEM_H__

