#ifndef TIGINE_GRAPHIC_INTERFACE_I_RENDER_PASS_H_
#define TIGINE_GRAPHIC_INTERFACE_I_RENDER_PASS_H_

#include "interface/i_common.h"

#include <vector>

namespace tigine { namespace graphic {
enum class AttachmentLoadOp {
    Undefined,
    Load,
    Clear
};

enum class AttachmentStoreOp {
    Undefined,
    Store
};

struct AttachmentFormat {
    DataFormat        format = DataFormat::Undefined;
    AttachmentLoadOp  load   = AttachmentLoadOp::Undefined;
    AttachmentStoreOp store  = AttachmentStoreOp::Undefined;
};

struct RenderPassDesc {
    std::vector<AttachmentFormat> color_attachments;
    AttachmentFormat              depth_attachment;
    AttachmentFormat              stencil_attachment;
    TUInt                         samples = 1;
};

class IRenderPass : public NonCopyable {};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_RENDER_PASS_H_
