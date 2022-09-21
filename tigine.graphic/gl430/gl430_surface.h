#ifndef TIGINE_GRAPHIC_GL430_GL430_SURFACE_H_
#define TIGINE_GRAPHIC_GL430_GL430_SURFACE_H_

#include "gl430/gl430_common.h"
#include "interface/i_surface.h"

namespace tigine { namespace graphic {
class GL430RenderContext;
class GL430Surface : public ISurface {
public:
    GL430Surface()  = default;
    ~GL430Surface() = default;
    DISALLOW_COPY_AND_ASSIGN(GL430Surface);

    void setTitle(const std::string &name) override {
        glfwSetWindowTitle(window_, name.c_str());
    }
    void show() override { glfwShowWindow(window_); }
    bool processEvents() override {
        glfwPollEvents();
        return !glfwWindowShouldClose(window_);
    }

private:
    friend class GL430RenderContext;
    GLFWwindow *window_ = nullptr;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_GL430_GL430_SURFACE_H_
