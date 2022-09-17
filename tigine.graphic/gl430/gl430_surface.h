#ifndef TIGINE_GRAPHIC_GL430_GL430_SURFACE_H_
#define TIGINE_GRAPHIC_GL430_GL430_SURFACE_H_

#include "gl430/gl430_common.h"

namespace tigine {
namespace graphic {
class GL430RenderContext;
class GL430Surface {
    friend class GL430RenderContext;

public:
    GL430Surface() = default;
    ~GL430Surface() = default;
    DISALLOW_COPY_AND_ASSIGN(GL430Surface);

    void setTitle(const std::string& name) {
        glfwSetWindowTitle(window_, name.c_str());
    }
    void show() { 
        glfwShowWindow(window_); 
    }
    bool processEvents() {
        glfwPollEvents();
        return !glfwWindowShouldClose(window_);
    }
    void present() {
        glfwSwapBuffers(window_); 
    }

private:
    GLFWwindow* window_ = nullptr;
};
} // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_GL430_GL430_SURFACE_H_
