#ifndef TIGINE_RHI_INTERFACE_I_BUFFER_ARRAY_H_
#define TIGINE_RHI_INTERFACE_I_BUFFER_ARRAY_H_

#include <vector>

#include "interface/i_common.h"
#include "interface/i_buffer.h"

namespace tigine { namespace rhi {
enum class IndexKind {
    IK_UINT16,
    IK_UINT32,
};

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
    IndexKind                  index_kind     = IndexKind::IK_UINT32;
    std::vector<BindingInfo>   bindings;
    std::vector<AttributeInfo> attributes;
};

class IBufferArray : public NonCopyable {};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_BUFFER_ARRAY_H_
