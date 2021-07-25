#ifndef __GL3PLUS_TEXTURE_2D_H__
#define __GL3PLUS_TEXTURE_2D_H__

#include "gl3plus_common.h"

namespace ti_render {
	class gl3plus_texture_2d {
	friend class gl3plus_shader;
	friend class gl3plus_frame_buffer;

	private:
		unsigned int m_id;
		unsigned int m_width;
		unsigned int m_height;
		color_format m_format;
		unsigned m_mipmap_layer_max;

	public:
		gl3plus_texture_2d(
			unsigned int width,
			unsigned int height,
			color_format format,
			bool mipmap = false);
		~gl3plus_texture_2d();

		void push_data(color_format format, void* data, unsigned int mipmap_layer = 0);
		const unsigned int& get_mipmap_layer_max(void) const {
			return m_mipmap_layer_max;
		}
		const color_format& get_color_format(void) const {
			return m_format;
		}
		unsigned int get_width(unsigned int mipmap_layer = 0) const;
		unsigned int get_height(unsigned int mipmap_layer = 0) const;
	};
}

#endif // !__GL3PLUS_TEXTURE_2D_H__
