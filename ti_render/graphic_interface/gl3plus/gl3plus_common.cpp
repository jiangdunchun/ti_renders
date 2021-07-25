#include "gl3plus_common.h"

namespace ti_render {
	GLuint map_cubemap_face(cubemap_face face) {
		return GL_TEXTURE_CUBE_MAP_POSITIVE_X + (unsigned int)face;
	}

	GLuint map_color_internal_format(color_format format) {
		GLuint gl_internal_format = 0;
		switch (format) {
		case color_format::R8B:
			gl_internal_format = GL_R8;
			break;
		case color_format::RGB8B:
			gl_internal_format = GL_RGB8;
			break;
		case color_format::RGBA8B:
			gl_internal_format = GL_RGBA8;
			break;
		case color_format::R16F:
			gl_internal_format = GL_R16F;
			break;
		case color_format::RGB16F:
			gl_internal_format =  GL_RGB16F;
			break;
		case color_format::RGBA16F:
			gl_internal_format = GL_RGBA16F;
			break;
		default:
			break;
		}
		return gl_internal_format;
	}

	GLuint map_color_format(color_format format) {
		GLuint gl_format = 0;
		switch (format) {
		case color_format::R8B:
		case color_format::R16F:
			gl_format = GL_RED;
			break;
		case color_format::RGB8B:
		case color_format::RGB16F:
			gl_format = GL_RGB;
			break;
		case color_format::RGBA8B:
		case color_format::RGBA16F:
			gl_format = GL_RGBA;
			break;
		default:
			break;
		}
		return gl_format;
	}

	GLuint map_color_data_type(color_format format) {
		GLuint gl_data_type = 0;
		switch (format) {
		case color_format::R8B:
		case color_format::RGB8B:
		case color_format::RGBA8B:
			gl_data_type = GL_UNSIGNED_BYTE;
			break;
		case color_format::R16F:
		case color_format::RGB16F:
		case color_format::RGBA16F:
			gl_data_type = GL_FLOAT;
			break;
		default:
			break;
		}
		return gl_data_type;
	}

	GLuint map_frame_buffer(int mask) {
		GLuint fb_mask = 0;
		if (mask & (char)frame_buffer_type::COLOR) fb_mask |= GL_COLOR_BUFFER_BIT;
		if (mask & (char)frame_buffer_type::DEPTH) fb_mask |= GL_DEPTH_BUFFER_BIT;
		if (mask & (char)frame_buffer_type::STENCIL) fb_mask |= GL_STENCIL_BUFFER_BIT;
		return fb_mask;
	}
}