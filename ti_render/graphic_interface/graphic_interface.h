#ifndef __GRAPHIC_INTERFACE_H__
#define __GRAPHIC_INTERFACE_H__

#ifdef GL3PLUS
#include "gl3plus/gl3plus_render_system.h"
#include "gl3plus/gl3plus_frame_buffer.h"
#include "gl3plus/gl3plus_vertex_buffer.h"
#include "gl3plus/gl3plus_texture_2d.h"
#include "gl3plus/gl3plus_texture_cube.h"
#include "gl3plus/gl3plus_shader.h"
#endif // GL3PLUS

namespace ti_render {
#ifdef GL3PLUS
	typedef gl3plus_render_system			render_system;
	typedef gl3plus_frame_buffer			frame_buffer;
	typedef gl3plus_vertex_buffer			vertex_buffer;
	typedef gl3plus_texture_2d				texture_2d;
	typedef gl3plus_texture_cube			texture_cube;
	typedef gl3plus_shader					shader;
#endif // GL3PLUS
}

#endif // !__GRAPHIC_INTERFACE_H__

