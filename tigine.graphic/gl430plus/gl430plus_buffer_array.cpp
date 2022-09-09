#include "gl430plus_buffer_array.h"

namespace tigine {
	inline GLenum map_data_format(data_format format) {
		int type = format & 0xf0;
		switch (type) {
		case (FLOAT):
			return GL_FLOAT;
			break;
		default:
			return 0;
			break;
		}
	}

	gl430plus_buffer_array::gl430plus_buffer_array(const buffer_array_descriptor& desc) {
		glGenVertexArrays(1, &m_id);
		glBindVertexArray(m_id);

		glBindBuffer(GL_ARRAY_BUFFER, desc.vertices_buffer->get_id());
		if (desc.indices_buffer) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, desc.indices_buffer->get_id());
		
		for (auto& attribute : desc.vertex_attributes) {
			glEnableVertexAttribArray(attribute.location);
			glVertexAttribPointer(
				attribute.location,
				attribute.format & 0x0f, map_data_format(attribute.format), GL_FALSE,
				attribute.stride,
				(void*)attribute.offset);
		}
	}

	gl430plus_buffer_array::~gl430plus_buffer_array() {
		glDeleteVertexArrays(1, &m_id);
	}
}