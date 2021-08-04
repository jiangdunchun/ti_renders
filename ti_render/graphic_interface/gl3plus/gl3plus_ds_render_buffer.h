#ifndef __GL3PLUS_DS_RENDER_BUFFER_H__
#define __GL3PLUS_DS_RENDER_BUFFER_H__

#include "gl3plus_common.h"

namespace ti_render {
	class gl3plus_ds_render_buffer {
	friend class gl3plus_frame_buffer;

	private:
		unsigned int m_width;
		unsigned int m_height;
		GLuint m_id;

	public:
		gl3plus_ds_render_buffer(unsigned width, unsigned height);
		~gl3plus_ds_render_buffer();
	};
}

#endif // !__GL3PLUS_DS_RENDER_BUFFER_H__