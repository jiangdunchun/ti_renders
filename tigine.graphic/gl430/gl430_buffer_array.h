#ifndef TIGINE_GRAPHIC_GL430_GL430_BUFFER_ARRAY_H_
#define TIGINE_GRAPHIC_GL430_GL430_BUFFER_ARRAY_H_

#include <vector>

#include "gl430/gl430_common.h"
#include "gl430/gl430_buffer.h"

namespace tigine {
namespace graphic {
struct VertexAttribute {
    DataFormat format;
    std::uint32_t location;
    std::uint32_t offset;
    std::uint32_t stride;
};

struct BufferArrayDescriptor {
    GL430Buffer* vertices_buffer;
    GL430Buffer* indices_buffer = nullptr;
    std::vector<VertexAttribute> vertex_attributes;
};

class GL430BufferArray {
public:
    explicit GL430BufferArray(const BufferArrayDescriptor& desc);
    ~GL430BufferArray();
    DISALLOW_COPY_AND_ASSIGN(GL430BufferArray);

    GLuint getID() const {
        return id_;
    }

private:
    GLuint id_;
};
} // namespace tigine::graphic
} // namespace tigine 

#endif // !TIGINE_GRAPHIC_GL430_GL430_BUFFER_ARRAY_H_
