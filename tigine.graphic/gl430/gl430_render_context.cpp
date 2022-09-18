#include "gl430/gl430_render_context.h"

namespace tigine {
namespace graphic {
GL430RenderContext::GL430RenderContext(const RenderContextDescriptor& desc) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	surface_ = new GL430Surface();
    surface_->window_ = glfwCreateWindow(desc.width, desc.height, "", NULL, NULL);
    if (!surface_->window_) {
		// @TODO
        glfwTerminate();
    }
    glfwMakeContextCurrent(surface_->window_);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    RenderPassDescriptor  render_pass_desc;
    render_pass_ = new GL430RenderPass(render_pass_desc);
}

GL430RenderContext::~GL430RenderContext() {
    if (surface_->window_) glfwDestroyWindow(surface_->window_);
    delete surface_;
    delete render_pass_;
    glfwTerminate();
}
} // namepace tigine::graphic
} // namespace tigine