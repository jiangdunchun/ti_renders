#include "gl3plus_render_system.h"

using namespace std;

namespace ti_render {
	bool gl3plus_render_system::init(unsigned int width, unsigned int height, const string& name) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(width, height, name.data(), NULL, NULL);
		if (m_window == nullptr) {
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return false;

		return true;
	}

	void gl3plus_render_system::shutdown(void) {
		glfwTerminate();
	}

	bool gl3plus_render_system::get_active(void){
		return !glfwWindowShouldClose(m_window);
	}

	void gl3plus_render_system::set_clear_color(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void gl3plus_render_system::set_resolution(unsigned int width, unsigned int height) {
		glViewport(0, 0, width, height);
	}

	void gl3plus_render_system::clear_frame_buffer(char mask) {
		glClear(map_frame_buffer(mask));
	}

	void gl3plus_render_system::set_depth_test_enabled(bool enabled) {
		if (enabled) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);
	}

	void gl3plus_render_system::pre_rend_one_frame(void) {
		glfwPollEvents();
	}

	void gl3plus_render_system::post_rend_one_frame(void) {
		glfwSwapBuffers(m_window);
	}
}