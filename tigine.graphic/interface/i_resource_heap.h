#ifndef TIGINE_GRAPHIC_INTERFACE_I_RESOURCE_HEAP_H_
#define TIGINE_GRAPHIC_INTERFACE_I_RESOURCE_HEAP_H_

#include "interface/i_common.h"

#include "interface/i_resource.h"
#include "interface/i_texture.h"
#include "interface/i_shader.h"

namespace tigine { namespace graphic {
struct UniformInfo {
    TUInt      binding;
    IResource *resource = nullptr;
    ShaderKind shader_stage;
};

struct ResourceHeapDesc {
    TUInt        uniforms_count;
    UniformInfo *uniforms;
};

class IResourceHeap : public NonCopyable {};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_RESOURCE_HEAP_H_
