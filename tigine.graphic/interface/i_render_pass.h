#ifndef TIGINE_GRAPHIC_INTERFACE_I_RENDER_PASS_H_
#define TIGINE_GRAPHIC_INTERFACE_I_RENDER_PASS_H_

#include "interface/i_common.h"

#include <vector>

namespace tigine { namespace graphic {
enum class AttachmentLoadOption {
    Undefined,
    Load,
    Clear
};

enum class AttachmentStoreOption {
    Undefined,
    Store
};

struct AttachmentDescriptor {
    DataFormat            format = DataFormat::Undefined;
    AttachmentLoadOption  load   = AttachmentLoadOption::Undefined;
    AttachmentStoreOption store  = AttachmentStoreOption::Undefined;
};

struct RenderPassDescriptor {
    std::vector<AttachmentDescriptor> color_attachments;
    AttachmentDescriptor              depth_attachment;
    AttachmentDescriptor              stencil_attachment;
    TUInt                             samples = 1;
};

class IRenderPass : public NonCopyable {};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_RENDER_PASS_H_
