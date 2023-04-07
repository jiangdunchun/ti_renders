#ifndef TIGINE_RHI_INTERFACE_I_RENDER_TARGET_H_
#define TIGINE_RHI_INTERFACE_I_RENDER_TARGET_H_

#include "interface/i_common.h"
#include "interface/i_render_pass.h"
#include "interface/i_texture.h"

namespace tigine { namespace rhi {
enum class AttachmentKind {
    Color,
    Depth,
    DepthStencil,
    Stencil,
};

struct AttachmentDesc {
    AttachmentKind kind;
    ITexture      *texture;
    TUInt          mip_level   = 0;
    TUInt          array_layer = 0;
};

struct RenderTargetDesc {
    Extent2D                    resolution;
    TUInt                       samples = 1;
    IRenderPass                *render_pass;
    std::vector<AttachmentDesc> attachments;
};

class IRenderTarget : public NonCopyable {
public:
    virtual ~IRenderTarget() = default;

    virtual bool isContext() { return false; }

    virtual IRenderPass *getRenderPass()                = 0;
    virtual Extent2D     getResolution()                = 0;
    virtual TUInt        getSamples()                   = 0;
    virtual TUInt        getNumColorAttachments() const = 0;
    virtual bool         hasDepthAttachment() const     = 0;
    virtual bool         hasStencilAttachment() const   = 0;
    
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_RENDER_TARGET_H_
