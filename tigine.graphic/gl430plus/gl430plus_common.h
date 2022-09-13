#ifndef __GL430PLUS_COMMON_H__
#define __GL430PLUS_COMMON_H__

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace tigine {
    enum data_format {
        R = 0x01,
        RG = 0x02,
        RGB = 0x03,
        RGBA = 0x04,

        UINT = 0x10,
        INT = 0x20,
        FLOAT = 0x30,

        RGB32Float = RGB | FLOAT,
    };
}

#endif // !__GL430PLUS_COMMON_H__

