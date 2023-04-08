#ifndef TIGINE_RHI_INTERFACE_I_RENDER_PASS_H_
#define TIGINE_RHI_INTERFACE_I_RENDER_PASS_H_

#include "interface/i_common.h"

namespace tigine { namespace rhi {
enum class AttachmentLoadOp {
    DontCare,
    Load,
    Clear
};

enum class AttachmentStoreOp { 
    DontCare,
    Store
};

struct AttachmentDesc {
    DataFormat        format;
    AttachmentLoadOp  load   = AttachmentLoadOp::DontCare;
    AttachmentStoreOp store  = AttachmentStoreOp::DontCare;
};

struct RenderPassDesc {
    TVector<AttachmentDesc> color_attachments;
    AttachmentDesc          depth_attachment;
    AttachmentDesc          stencil_attachment;
    TUInt                   samples = 1;
};

class IRenderPass : public NonCopyable {
public:
    virtual ~IRenderPass() = default;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_RENDER_PASS_H_
