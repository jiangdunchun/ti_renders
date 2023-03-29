#ifndef TIGINE_RHI_INTERFACE_I_BUFFER_H_
#define TIGINE_RHI_INTERFACE_I_BUFFER_H_

#include "interface/i_common.h"
#include "interface/i_resource.h"

namespace tigine { namespace rhi {
enum class BufferKind {
    Uniform,
    Vertices,
    Indices,
};

struct BufferDesc {
    BufferKind kind;
    TULong     data_size;
    void      *data  = nullptr;
};

class IBuffer : public IResource {
public:
    ResourceKind getResourceKind() const override final { return ResourceKind::Buffer; }

    virtual void updateData(TULong data_size, void *data) = 0;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_BUFFER_H_
