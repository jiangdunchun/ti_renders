#ifndef __GL430PLUS_FRAME_BUFFER_H__
#define __GL430PLUS_FRAME_BUFFER_H__

#include <vector>
#include "gl430plus_common.h"
#include "gl430plus_ds_render_buffer.h"
#include "gl430plus_texture_2d.h"
#include "gl430plus_texture_cube.h"

namespace ti_render {
	class gl430plus_frame_buffer {
	private:
		unsigned int m_width;
		unsigned int m_height;
		GLuint m_id;
		std::vector<GLuint> m_attachments;
		gl430plus_ds_render_buffer* m_ds_rbo;

	public:
		gl430plus_frame_buffer(unsigned int width, unsigned int height, gl430plus_ds_render_buffer* ds_rbo = nullptr);
		~gl430plus_frame_buffer();
		void attach_color_buffer(unsigned int attachment, gl430plus_texture_2d* texture, unsigned int mipmap_layer = 0);
		void attach_color_buffer(unsigned int attachment, gl430plus_texture_cube* texture, cubemap_face face, unsigned int mipmap_layer = 0);
		void detach_color_buffer(unsigned int attachment);
		void bind(void) const;
	};
}

#endif // !__GL430PLUS_FRAME_BUFFER_H__