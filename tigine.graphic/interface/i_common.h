#ifndef TIGINE_GRAPHIC_INTERFACE_I_COMMON_H_
#define TIGINE_GRAPHIC_INTERFACE_I_COMMON_H_

#include <cstdint>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  void operator=(const TypeName&) = delete

namespace tigine { namespace graphic {
typedef std::uint8_t  TChar;
typedef std::uint16_t TUShort;
typedef std::int16_t  TShort;
typedef std::uint32_t TUInt;
typedef std::int32_t  TInt;
typedef std::uint64_t TULong;
typedef std::int64_t  TLong;

enum DataFormat : TUShort {
    DF_R    = 0x01,
    DF_RG   = 0x02,
    DF_RGB  = 0x03,
    DF_RGBA = 0x04,

    DF_Uint  = 0x10,
    DF_Int   = 0x20,
    DF_Float = 0x30,

    DF_RGB32Float = DF_RGB | DF_Float,
};

enum ClearFlag : TChar {
    CF_Color   = 1 << 0,
    CF_Depth   = 1 << 1,
    CF_Stencil = 1 << 2
};

enum class DrawMode {
    Triangles,
};

struct Viewport {
    TUInt x;
    TUInt y;
    TUInt width;
    TUInt height;
};

struct ClearValue {
    float color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float depth    = 1.0f;
    int   stencil  = 0;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_COMMON_H_
