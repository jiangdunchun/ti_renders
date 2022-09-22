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

    surface_                    = new GL430Surface();
    GL430Surface *gl430_surface = static_cast<GL430Surface *>(surface_);
    gl430_surface->window_      = glfwCreateWindow(desc.width, desc.height, "", NULL, NULL);
    if (!gl430_surface->window_) {
        // @TODO
        glfwTerminate();
    }
    glfwMakeContextCurrent(gl430_surface->window_);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    RenderPassDescriptor render_pass_desc;
    render_pass_ = new GL430RenderPass(render_pass_desc);
}

GL430RenderContext::~GL430RenderContext() {
    GL430Surface *gl430_surface = static_cast<GL430Surface *>(surface_);
    if (gl430_surface->window_) glfwDestroyWindow(gl430_surface->window_);
    delete surface_;
    delete render_pass_;
    glfwTerminate();
}
}} // namespace tigine::graphic