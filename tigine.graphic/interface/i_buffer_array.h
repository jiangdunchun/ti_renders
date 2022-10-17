#ifndef TIGINE_GRAPHIC_INTERFACE_I_BUFFER_ARRAY_H_
#define TIGINE_GRAPHIC_INTERFACE_I_BUFFER_ARRAY_H_

#include "interface/i_common.h"
#include "interface/i_buffer.h"

namespace tigine { namespace graphic {
struct AttributeInfo {
    DataFormat format;
    TUInt      location;
    TUInt      offset;
    TUInt      stride;
};

struct BufferArrayDescriptor {
    IBuffer       *vertices_buffer;
    IBuffer       *indices_buffer = nullptr;
    TUInt          attributes_count;
    AttributeInfo *vertex_attributes;
};

class IBufferArray : public NonCopyable {};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_BUFFER_ARRAY_H_
