#ifndef TIGINE_GRAPHIC_INTERFACE_I_BUFFER_ARRAY_H_
#define TIGINE_GRAPHIC_INTERFACE_I_BUFFER_ARRAY_H_

#include "interface/i_common.h"
#include "interface/i_buffer.h"

namespace tigine { namespace graphic {
struct BindingInfo {
    TUInt binding;
    TUInt stride;
};

struct AttributeInfo {
    TUInt      binding;
    DataFormat format;
    TUInt      location;
    TUInt      offset;
};

struct BufferArrayDescriptor {
    IBuffer       *vertices_buffer;
    IBuffer       *indices_buffer = nullptr;
    TUInt          bindings_count;
    BindingInfo   *bindings;
    TUInt          attributes_count;
    AttributeInfo *attributes;
};

class IBufferArray : public NonCopyable {};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_BUFFER_ARRAY_H_
