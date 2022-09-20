#ifndef TIGINE_GRAPHIC_GL430_GL430_RENDER_CONTEXT_H_
#define TIGINE_GRAPHIC_GL430_GL430_RENDER_CONTEXT_H_

#include <cstdint>
#include <string>

#include "gl430/gl430_common.h"
#include "gl430/gl430_surface.h"
#include "gl430/gl430_render_pass.h"

namespace tigine { namespace graphic {
struct RenderContextDescriptor {
    std::uint32_t width;
    std::uint32_t height;
    std::uint32_t samples = 1;
};

class GL430RenderContext {
public:
    GL430RenderContext(const RenderContextDescriptor &desc);
    ~GL430RenderContext();
    DISALLOW_COPY_AND_ASSIGN(GL430RenderContext);

    GL430Surface    *getSurface() { return surface_; }
    GL430RenderPass *getRenderPass() { return render_pass_; }
    Viewport         getResolution() { return {0, 0, 600, 600}; }
    void             present() const { glfwSwapBuffers(surface_->window_); }

private:
    GL430Surface    *surface_;
    GL430RenderPass *render_pass_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_GL430_GL430_RENDER_CONTEXT_H_