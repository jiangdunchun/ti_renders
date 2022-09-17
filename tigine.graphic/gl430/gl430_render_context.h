#ifndef TIGINE_GRAPHIC_GL430_GL430_RENDER_CONTEXT_H_
#define TIGINE_GRAPHIC_GL430_GL430_RENDER_CONTEXT_H_

#include <cstdint>
#include <string>

#include "gl430/gl430_common.h"

namespace tigine {
namespace graphic {
struct RenderContextDescriptor {
    std::uint32_t width;
    std::uint32_t height;
    std::uint32_t samples = 1;
};

class GL430RenderContext;
class GL430Surface {
    friend class GL430RenderContext;

public:
    GL430Surface() = default;
    ~GL430Surface() = default;
    DISALLOW_COPY_AND_ASSIGN(GL430Surface);

    void setTitle(const std::string& name) { glfwSetWindowTitle(window_, name.c_str()); }
    void show() { glfwShowWindow(window_); }
    bool processEvents() {
        glfwPollEvents();
        return !glfwWindowShouldClose(window_);
    }
    void present() { glfwSwapBuffers(window_); }

private:
    GLFWwindow* window_ = nullptr;
};

class GL430RenderContext {
public:
    GL430RenderContext(const RenderContextDescriptor& desc);
    ~GL430RenderContext();
    DISALLOW_COPY_AND_ASSIGN(GL430RenderContext);

    GL430Surface* surface() { return surface_; }

private:
    GL430Surface* surface_;
};
} // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_GL430_GL430_RENDER_CONTEXT_H_