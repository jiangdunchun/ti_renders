#ifndef TIGINE_GRAPHIC_INTERFACE_I_RENDER_TARGET_H_
#define TIGINE_GRAPHIC_INTERFACE_I_RENDER_TARGET_H_

#include "interface/i_common.h"

#include "interface/i_render_pass.h"

namespace tigine { namespace graphic {
struct RenderTargetDescriptor {};

class IRenderTarget {
public:
    virtual Extent2D           getResolution()                = 0;
    virtual TUInt              getSamples()                   = 0;
    virtual TUInt              getNumColorAttachments() const = 0;
    virtual bool               hasDepthAttachment() const     = 0;
    virtual bool               hasStencilAttachment() const   = 0;

    IRenderPass* getRenderPass() { return render_pass_; }

protected:
    IRenderPass *render_pass_ = nullptr;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_RENDER_TARGET_H_
