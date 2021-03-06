#ifndef __GL430PLUS_TEXTURE_CUBE_H__
#define __GL430PLUS_TEXTURE_CUBE_H__

#include "gl430plus_common.h"

namespace ti_render {
	class gl430plus_texture_cube {
		friend class gl430plus_shader;
		friend class gl430plus_compute_shader;
		friend class gl430plus_frame_buffer;

	private:
		unsigned int m_id;
		unsigned int m_width;
		unsigned int m_height;
		color_format m_format;
		unsigned m_mipmap_layer_max;

	public:
		gl430plus_texture_cube(unsigned int width, unsigned int height, color_format format);
		~gl430plus_texture_cube();

		void push_data(cubemap_face face, color_format format, void* data, unsigned int mipmap_layer = 0);
		const unsigned int& get_mipmap_layer_max(void) const {
			return m_mipmap_layer_max;
		}
		const color_format& get_color_format(void) const {
			return m_format;
		}
		void generate_mipmap(void);
		unsigned int get_width(unsigned int mipmap_layer = 0) const;
		unsigned int get_height(unsigned int mipmap_layer = 0) const;
	};
}

#endif //!__GL430PLUS_TEXTURE_CUBE_H__
