#ifndef TIGINE_RHI_INTERFACE_I_RENDER_CONTEXT_H_
#define TIGINE_RHI_INTERFACE_I_RENDER_CONTEXT_H_

#include "interface/i_common.h"
#include "interface/i_render_pass.h"
#include "interface/i_render_target.h"
#include "interface/i_surface.h"

namespace tigine { namespace rhi {
struct RenderContextDesc {
    Extent2D resolution;
    TUInt    samples = 1;
};

class IRenderContext : public IRenderTarget {
public:
    virtual ~IRenderContext() = default;

    virtual bool isContext() override final { return true; }

    virtual ISurface *getSurface() = 0;
    virtual void      present()    = 0;
    
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_RENDER_CONTEXT_H_