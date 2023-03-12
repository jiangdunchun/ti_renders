#ifndef TIGINE_RHI_INTERFACE_I_RESOURCE_HEAP_H_
#define TIGINE_RHI_INTERFACE_I_RESOURCE_HEAP_H_

#include <vector>

#include "interface/i_common.h"
#include "interface/i_resource.h"
#include "interface/i_texture.h"
#include "interface/i_shader.h"

namespace tigine { namespace rhi {
struct UniformInfo {
    TUInt      binding;
    IResource *resource = nullptr;
    ShaderKind shader_stage;
};

struct ResourceHeapDesc {
    std::vector<UniformInfo> uniforms;
};

class IResourceHeap : public NonCopyable {};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_RESOURCE_HEAP_H_
