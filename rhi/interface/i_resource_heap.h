#ifndef TIGINE_RHI_INTERFACE_I_RESOURCE_HEAP_H_
#define TIGINE_RHI_INTERFACE_I_RESOURCE_HEAP_H_

#include "interface/i_common.h"
#include "interface/i_resource.h"
#include "interface/i_texture.h"
#include "interface/i_shader.h"

namespace tigine { namespace rhi {
struct UniformDesc {
    TUInt      binding;
    IResource *resource;
    ShaderKind shader_stage;
};

struct ResourceHeapDesc {
    TVector<UniformDesc> uniforms;
};

class IResourceHeap : public NonCopyable {
public:
    virtual ~IResourceHeap() = default;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_RESOURCE_HEAP_H_
