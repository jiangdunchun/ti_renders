#ifndef TIGINE_RHI_INTERFACE_I_RESOURCE_H_
#define TIGINE_RHI_INTERFACE_I_RESOURCE_H_

#include "interface/i_common.h"

namespace tigine { namespace rhi {
enum class ResourceKind {
    Buffer,
    Texture
};

class IResource : public NonCopyable {
public:
    virtual ResourceKind getResourceKind() const = 0;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_RESOURCE_H_
