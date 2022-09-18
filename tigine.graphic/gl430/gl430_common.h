#ifndef TIGINE_GRAPHIC_GL430_GL430_COMMON_H_
#define TIGINE_GRAPHIC_GL430_GL430_COMMON_H_

#include <glad/glad.h>
#include <glfw/glfw3.h>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  void operator=(const TypeName&) = delete

namespace tigine {
namespace graphic {
enum DataFormat {
    DF_R = 0x01,
    DF_RG = 0x02,
    DF_RGB = 0x03,
    DF_RGBA = 0x04,

    DF_Uint = 0x10,
    DF_Int = 0x20,
    DF_Float = 0x30,

    DF_RGB32Float = DF_RGB | DF_Float,
};

enum ClearFlag {
    CF_Color = 1 << 0,
    CF_Depth = 1 << 1,
    CF_Stencil = 1 << 2
};
} // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_GL430_GL430_COMMON_H_

