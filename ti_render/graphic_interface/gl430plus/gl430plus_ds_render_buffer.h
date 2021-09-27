#ifndef __GL430PLUS_DS_RENDER_BUFFER_H__
#define __GL430PLUS_DS_RENDER_BUFFER_H__

#include "gl430plus_common.h"

namespace ti_render {
	class gl430plus_ds_render_buffer {
	friend class gl430plus_frame_buffer;

	private:
		unsigned int m_width;
		unsigned int m_height;
		GLuint m_id;

	public:
		gl430plus_ds_render_buffer(unsigned width, unsigned height);
		~gl430plus_ds_render_buffer();
	};
}

#endif // !__GL430PLUS_DS_RENDER_BUFFER_H__