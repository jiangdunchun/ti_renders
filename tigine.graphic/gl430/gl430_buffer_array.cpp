#include "gl430/gl430_buffer_array.h"

namespace tigine {
namespace graphic {
namespace {
GLenum mapDataFormat(DataFormat format) {
	int type = format & 0xf0;
	switch (type) {
	case (DF_Float):
		return GL_FLOAT;
		break;
	default:
		return 0;
		break;
	}
}
} // namespace

GL430BufferArray::GL430BufferArray(const BufferArrayDescriptor& desc) {
	glGenVertexArrays(1, &id_);
	glBindVertexArray(id_);

	glBindBuffer(GL_ARRAY_BUFFER, desc.vertices_buffer->getID());
	if (desc.indices_buffer) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, desc.indices_buffer->getID());

	for (auto& attribute : desc.vertex_attributes) {
		glEnableVertexAttribArray(attribute.location);
		glVertexAttribPointer(
			attribute.location,
			attribute.format & 0x0f, 
			mapDataFormat(attribute.format),
			GL_FALSE,
			attribute.stride,
			(void*)attribute.offset);
	}
}

GL430BufferArray::~GL430BufferArray() {
	glDeleteVertexArrays(1, &id_);
}
} // namespace tigine::graphic
} // namspace tigine