#ifndef __GRAPHIC_INTERFACE_H__
#define __GRAPHIC_INTERFACE_H__

#ifdef GL430PLUS
#include "gl430plus/gl430plus_render_system.h"
#include "gl430plus/gl430plus_ds_render_buffer.h"
#include "gl430plus/gl430plus_frame_buffer.h"
#include "gl430plus/gl430plus_vertex_buffer.h"
#include "gl430plus/gl430plus_texture_2d.h"
#include "gl430plus/gl430plus_texture_cube.h"
#include "gl430plus/gl430plus_shader.h"
#endif // GL430PLUS

namespace ti_render {
#ifdef GL430PLUS
	typedef gl430plus_render_system			render_system;
	typedef gl430plus_ds_render_buffer		ds_render_buffer;
	typedef gl430plus_frame_buffer			frame_buffer;
	typedef gl430plus_vertex_buffer			vertex_buffer;
	typedef gl430plus_texture_2d			texture_2d;
	typedef gl430plus_texture_cube			texture_cube;
	typedef gl430plus_shader				shader;
#endif // GL430PLUS
}

#endif // !__GRAPHIC_INTERFACE_H__

