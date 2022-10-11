#include "gl430/gl430_render_context.h"

#include "gl430/gl430_render_pass.h"
#include "gl430/gl430_surface.h"

namespace tigine { namespace graphic {
GL430RenderContext::GL430RenderContext(const RenderContextDescriptor &desc) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    window_ = glfwCreateWindow(desc.resolution.width, desc.resolution.height, "", NULL, NULL);
    if (!window_) {
        // @TODO
        glfwTerminate();
    }

    glfwMakeContextCurrent(window_);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    surface_ = new GL430Surface(window_);

    RenderPassDescriptor render_pass_desc;
    render_pass_ = new GL430RenderPass(render_pass_desc);
}

GL430RenderContext::~GL430RenderContext() {
    if (window_) glfwDestroyWindow(window_);
    delete surface_;
    delete render_pass_;
    glfwTerminate();
}
}} // namespace tigine::graphic