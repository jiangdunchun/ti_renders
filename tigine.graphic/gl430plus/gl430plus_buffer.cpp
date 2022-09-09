#include "gl430plus_buffer.h"

namespace tigine {
	inline GLsizei map_buffer_flags(std::uint32_t flags) {
		GLsizei type = 0;
		if ((flags & ARRAY_BUFFER) > 0) type |= GL_ARRAY_BUFFER;
		if ((flags & ELEMENT_ARRAY_BUFFER) > 0) type |= GL_ELEMENT_ARRAY_BUFFER;
		return type;
	}

	gl430plus_buffer::gl430plus_buffer(
		const buffer_descriptor& desc,
		const void* data) : m_flags(desc.flags) {
		GLsizei buffer_type = map_buffer_flags(m_flags);
		glGenBuffers(1, &m_id);
		glBindBuffer(buffer_type, m_id);
		glBufferData(buffer_type, desc.size, data, GL_STATIC_DRAW);
	}

	gl430plus_buffer::~gl430plus_buffer() {
		glDeleteBuffers(1, &m_id);
	}
}