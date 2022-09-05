#ifndef __GL430PLUS_SURFACE_H__
#define __GL430PLUS_SURFACE_H__

#include <string>
#include "gl430plus_common.h"

namespace tigine {
	class gl430plus_render_context;
	class gl430plus_surface {
		friend class gl430plus_render_context;
	private:
		GLFWwindow* m_window;

	public:
		void set_title(const std::string& name) {
			glfwSetWindowTitle(m_window, name.c_str());
		}

		void show() {
			glfwShowWindow(m_window);
		}
	};
}

#endif // !__GL430PLUS_SURFACE_H__
