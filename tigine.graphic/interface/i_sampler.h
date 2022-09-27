#ifndef TIGINE_GRAPHIC_INTERFACE_I_SAMPLER_H_
#define TIGINE_GRAPHIC_INTERFACE_I_SAMPLER_H_

#include "interface/i_common.h"
#include "interface/i_resource.h"

namespace tigine { namespace graphic {
struct SamplerDescriptor {};

class ISampler : IResource {
public:
    ResourceKind getResourceKind() const override final { return ResourceKind::Sampler; }
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_SAMPLER_H_
