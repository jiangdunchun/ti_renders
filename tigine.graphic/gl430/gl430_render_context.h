#ifndef TIGINE_GRAPHIC_GL430_GL430_RENDER_CONTEXT_H_
#define TIGINE_GRAPHIC_GL430_GL430_RENDER_CONTEXT_H_

#include <string>

#include "gl430/gl430_common.h"
#include "gl430/gl430_surface.h"
#include "interface/i_render_context.h"

namespace tigine { namespace graphic {
class GL430RenderContext : public IRenderContext {
public:
    GL430RenderContext(const RenderContextDescriptor &desc);
    ~GL430RenderContext();
    DISALLOW_COPY_AND_ASSIGN(GL430RenderContext);

    Extent2D getResolution() override { return {600, 600}; }
    void     present() override { glfwSwapBuffers(static_cast<GL430Surface *>(surface_)->window_); }

    TUInt getSamples() override { return 1; }
    TUInt getNumColorAttachments() const override { return 0; }
    bool  hasDepthAttachment() const override { return 0; }
    bool  hasStencilAttachment() const override { return 0; }
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_GL430_GL430_RENDER_CONTEXT_H_