#ifndef TIGINE_GRAPHIC_INTERFACE_I_BUFFER_ARRAY_H_
#define TIGINE_GRAPHIC_INTERFACE_I_BUFFER_ARRAY_H_

#include <vector>

#include "interface/i_common.h"
#include "interface/i_buffer.h"

namespace tigine { namespace graphic {
struct VertexAttribute {
    DataFormat    format;
    std::uint32_t location;
    std::uint32_t offset;
    std::uint32_t stride;
};

struct BufferArrayDescriptor {
    IBuffer                      *vertices_buffer;
    IBuffer                      *indices_buffer = nullptr;
    std::vector<VertexAttribute> vertex_attributes;
};

class IBufferArray {};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_BUFFER_ARRAY_H_
