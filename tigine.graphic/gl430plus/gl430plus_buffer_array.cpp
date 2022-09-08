#include "gl430plus_buffer_array.h"

namespace tigine {
	gl430plus_buffer_array::gl430plus_buffer_array(const buffer_array_descriptor& desc) {
		glGenVertexArrays(1, &m_id);
		glBindVertexArray(m_id);

		glBindBuffer(GL_ARRAY_BUFFER, desc.vertices_buffer->get_id());
		if (desc.indices_buffer) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, desc.indices_buffer->get_id());

	}

	gl430plus_buffer_array::~gl430plus_buffer_array() {
		glDeleteVertexArrays(1, &m_id);
	}
}