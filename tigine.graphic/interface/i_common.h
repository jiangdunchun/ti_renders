#ifndef TIGINE_GRAPHIC_INTERFACE_I_COMMON_H_
#define TIGINE_GRAPHIC_INTERFACE_I_COMMON_H_

#include <cstdint>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  void operator=(const TypeName&) = delete

namespace tigine { namespace graphic {
enum DataFormat {
    DF_R    = 0x01,
    DF_RG   = 0x02,
    DF_RGB  = 0x03,
    DF_RGBA = 0x04,

    DF_Uint  = 0x10,
    DF_Int   = 0x20,
    DF_Float = 0x30,

    DF_RGB32Float = DF_RGB | DF_Float,
};

enum ClearFlag {
    CF_Color   = 1 << 0,
    CF_Depth   = 1 << 1,
    CF_Stencil = 1 << 2
};

enum class DrawMode {
    Triangles,
};

struct Viewport {
    std::uint32_t x;
    std::uint32_t y;
    std::uint32_t width;
    std::uint32_t height;
};

struct ClearValue {
    float color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float depth    = 1.0f;
    int   stencil  = 0;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_COMMON_H_
