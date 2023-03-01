#ifndef TIGINE_GRAPHIC_INTERFACE_I_BUFFER_ARRAY_H_
#define TIGINE_GRAPHIC_INTERFACE_I_BUFFER_ARRAY_H_

#include "interface/i_common.h"
#include "interface/i_buffer.h"

#include <vector>

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

struct BufferArrayDesc {
    IBuffer                   *vertices_buffer;
    IBuffer                   *indices_buffer = nullptr;
    std::vector<BindingInfo>   bindings;
    std::vector<AttributeInfo> attributes;
};

class IBufferArray : public NonCopyable {};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_BUFFER_ARRAY_H_
