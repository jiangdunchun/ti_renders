#ifndef TIGINE_RHI_GL430_GL430_RENDER_CONTEXT_H_
#define TIGINE_RHI_GL430_GL430_RENDER_CONTEXT_H_

#include <string>

#include "gl430/gl430_common.h"
#include "gl430/gl430_surface.h"
#include "gl430/gl430_render_pass.h"
#include "interface/i_render_context.h"

namespace tigine { namespace rhi {
class GL430RenderContext : public IRenderContext {
public:
    GL430RenderContext(const RenderContextDesc &desc);
    ~GL430RenderContext();

    ISurface* getSurface() override { return surface_; }
    void      present() override { glfwSwapBuffers(window_); }
    IRenderPass* getRenderPass() override { return render_pass_; }

    Extent2D getResolution() override { return {600, 600}; } //@TODO
    TUInt getSamples() override { return 0; } // @TODO
    TUInt getNumColorAttachments() const override { return 0; } // @TODO
    bool  hasDepthAttachment() const override { return 0; } // @TODO
    bool  hasStencilAttachment() const override { return 0; } // @TODO

private:
    GLFWwindow      *window_;
    GL430Surface    *surface_;
    GL430RenderPass *render_pass_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_GL430_GL430_RENDER_CONTEXT_H_