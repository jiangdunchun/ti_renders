#ifndef TIGINE_GRAPHIC_INTERFACE_I_BUFFER_H_
#define TIGINE_GRAPHIC_INTERFACE_I_BUFFER_H_

#include "interface/i_common.h"

#include "interface/i_resource.h"

namespace tigine { namespace graphic {
enum BufferKind {
    BK_Vertices = 1 << 0,
    BK_Indices  = 1 << 1,
};

struct BufferDescriptor {
    TULong size  = 0;
    TUInt  kinds = 0;
};

class IBuffer : public IResource {
public:
    ResourceKind getResourceKind() const override { return ResourceKind::Buffer; }
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_BUFFER_H_
