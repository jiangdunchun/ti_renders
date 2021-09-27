#include "gl430plus_ds_render_buffer.h"

using namespace std;

namespace ti_render {
	gl430plus_ds_render_buffer::gl430plus_ds_render_buffer(
		unsigned width,
		unsigned height) : m_width(width), m_height(height) {
		glGenRenderbuffers(1, &m_id);
		glBindRenderbuffer(GL_RENDERBUFFER, m_id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	}

	gl430plus_ds_render_buffer::~gl430plus_ds_render_buffer() {
		glDeleteRenderbuffers(1, &m_id);
	}
}


