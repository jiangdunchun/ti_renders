#ifndef TIGINE_RHI_INTERFACE_I_RENDER_PASS_H_
#define TIGINE_RHI_INTERFACE_I_RENDER_PASS_H_

#include "interface/i_common.h"

#include <vector>

namespace tigine { namespace rhi {
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
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_RENDER_PASS_H_
