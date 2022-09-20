#ifndef TIGINE_GRAPHIC_INTERFACE_I_RENDER_CONTEXT_H_
#define TIGINE_GRAPHIC_INTERFACE_I_RENDER_CONTEXT_H_

#include <string>

#include "interface/i_common.h"

namespace tigine { namespace graphic {
struct RenderContextDescriptor {
    std::uint32_t width;
    std::uint32_t height;
    std::uint32_t samples = 1;
};

class IRenderContext {};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_RENDER_CONTEXT_H_