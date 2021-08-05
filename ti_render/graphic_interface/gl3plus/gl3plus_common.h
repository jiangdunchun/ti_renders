#ifndef __GL3PLUS_COMMON_H__
#define __GL3PLUS_COMMON_H__

#include "../../common/tr_enum.h"
#include "../../common/tr_struct.h"
#include "../../common/logger_management.h"
#include "../../third_party/glad/glad.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>


namespace ti_render {
	GLuint map_cubemap_face(cubemap_face face);

	GLuint map_color_internal_format(color_format format);

	GLuint map_color_format(color_format format);

	GLuint map_color_data_type(color_format format);

	GLuint map_frame_buffer(int mask);

	GLuint map_graphic_capability(graphic_capability capacity);

	GLuint map_depth_func(depth_func func);
}

#endif // !__GL3PLUS_COMMON_H__

