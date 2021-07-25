#ifndef __GL3PLUS_FRAME_BUFFER_H__
#define __GL3PLUS_FRAME_BUFFER_H__

#include <vector>
#include "gl3plus_common.h"
#include "gl3plus_texture_2d.h"
#include "gl3plus_texture_cube.h"

namespace ti_render {
	class gl3plus_frame_buffer {
	private:
		unsigned int m_width;
		unsigned int m_height;
		GLuint m_id;
		GLuint m_ds_RBO;
		std::vector<GLuint> m_attachments;

	public:
		gl3plus_frame_buffer(unsigned width, unsigned height);
		~gl3plus_frame_buffer();
		void attach_color_buffer(unsigned int attachment, gl3plus_texture_2d* texture, unsigned int mipmap_layer = 0);
		void attach_color_buffer(unsigned int attachment, gl3plus_texture_cube* texture, cubemap_face face, unsigned int mipmap_layer = 0);
		void detach_color_buffer(unsigned int attachment);
		void bind(void) const;
		void unbind(void) const;
	};
}

#endif // !__GL3PLUS_FRAME_BUFFER_H__