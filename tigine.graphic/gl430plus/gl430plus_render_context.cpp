#include "gl430plus_render_context.h"

#include "gl430plus_common.h"

namespace tigine {
	gl430plus_render_context::gl430plus_render_context(const render_context_descriptor& desc)
		: m_desc(desc) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		m_surface.m_window = glfwCreateWindow(m_desc.width, m_desc.height, "", NULL, NULL);
		if (m_surface.m_window == nullptr) {
			glfwTerminate();
		}

		glfwMakeContextCurrent(m_surface.m_window);
	}

	gl430plus_render_context::~gl430plus_render_context() {
		glfwTerminate();
	}
}