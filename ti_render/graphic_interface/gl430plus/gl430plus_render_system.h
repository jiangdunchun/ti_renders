#ifndef __GL430PLUS_RENDER_SYSTEM_H__
#define __GL430PLUS_RENDER_SYSTEM_H__

#include <string>

#include "gl430plus_common.h"

namespace ti_render {
	class gl430plus_render_system {
	private:
		GLFWwindow* m_window;

	public:
		bool init(unsigned int width, unsigned int height, const std::string& name);
		void shutdown(void);
		bool is_active(void);
		void rend_to_screen(void);
		void set_clear_color(const glm::vec4& color);
		void set_resolution(unsigned int width, unsigned int height);
		void clear_frame_buffer(char mask);
		void set(graphic_capability capability, bool state);
		void set(graphic_func capability, bool state);
		void set_depth_func(depth_func func);
		void pre_rend_one_frame(void);
		void post_rend_one_frame(void);
	};
}

#endif // !__GL430PLUS_RENDER_SYSTEM_H__

