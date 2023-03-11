#include "gl430/gl430_buffer.h"

namespace tigine { namespace rhi {
namespace {
GLsizei mapBufferKinds(std::uint32_t kinds) {
    GLsizei type = 0;
    if ((kinds & BK_Vertices) > 0) type |= GL_ARRAY_BUFFER;
    if ((kinds & BK_Indices) > 0) type |= GL_ELEMENT_ARRAY_BUFFER;
    return type;
}
} // namespace

GL430Buffer::GL430Buffer(const BufferDescriptor &desc, const void *data) {
    GLsizei buffer_type = mapBufferKinds(desc.kinds);
    glGenBuffers(1, &id_);
    glBindBuffer(buffer_type, id_);
    glBufferData(buffer_type, desc.data_size, data, GL_STATIC_DRAW);
}

GL430Buffer::~GL430Buffer() { glDeleteBuffers(1, &id_); }
}} // namespace tigine::rhi