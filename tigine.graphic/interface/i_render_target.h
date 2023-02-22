#ifndef TIGINE_GRAPHIC_INTERFACE_I_RENDER_TARGET_H_
#define TIGINE_GRAPHIC_INTERFACE_I_RENDER_TARGET_H_

#include <vector>

#include "interface/i_common.h"

namespace tigine { namespace graphic {
class IRenderPass;
class ITexture;

enum class AttachmentKind {
    Color,
    Depth,
    DepthStencil,
    Stencil,
};

struct AttachmentDescriptor {
    AttachmentKind kind;
    ITexture      *texture;
    TUInt          mip_level;
    TUInt          array_layer;
};

struct RenderTargetDescriptor {
    IRenderPass                      *render_pass;
    Extent2D                          resolution;
    TUInt                             samples = 1;
    std::vector<AttachmentDescriptor> attachments;
};

class IRenderTarget : public NonCopyable {
public:
    virtual IRenderPass *getRenderPass()                = 0;
    virtual Extent2D     getResolution()                = 0;
    virtual TUInt        getSamples()                   = 0;
    virtual TUInt        getNumColorAttachments() const = 0;
    virtual bool         hasDepthAttachment() const     = 0;
    virtual bool         hasStencilAttachment() const   = 0;
    virtual bool         isContext() { return false; }
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_RENDER_TARGET_H_
