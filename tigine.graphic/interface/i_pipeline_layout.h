#ifndef TIGINE_GRAPHIC_INTERFACE_I_PIPELINE_LAYOUT_H_
#define TIGINE_GRAPHIC_INTERFACE_I_PIPELINE_LAYOUT_H_

#include "interface/i_common.h"

#include "interface/i_resource.h"
#include "interface/i_texture.h"

namespace tigine { namespace graphic {
struct UniformInfo {
    TUInt       binding;
    IResource  *resource = nullptr;
};

struct PipelineLayoutDescriptor {
    TUInt        uniforms_count;
    UniformInfo *uniforms;
};

class IPipelineLayout : public NonCopyable {};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_PIPELINE_LAYOUT_H_
