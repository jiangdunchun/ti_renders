#ifndef TIGINE_GRAPHIC_INTERFACE_I_RENDER_CONTEXT_H_
#define TIGINE_GRAPHIC_INTERFACE_I_RENDER_CONTEXT_H_

#include <string>

#include "interface/i_common.h"

#include "interface/i_render_pass.h"
#include "interface/i_surface.h"
#include "interface/i_render_target.h"

namespace tigine { namespace graphic {
struct RenderContextDescriptor {
    TUInt width;
    TUInt height;
    TUInt samples = 1;
};

class IRenderContext : public IRenderTarget {
public:
    ISurface        *getSurface() { return surface_; }
    virtual void     present()       = 0;

protected:
    ISurface    *surface_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_RENDER_CONTEXT_H_