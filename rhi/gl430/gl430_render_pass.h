#ifndef TIGINE_RHI_GL430_GL430_RENDER_PASS_H_
#define TIGINE_RHI_GL430_GL430_RENDER_PASS_H_

#include "gl430/gl430_common.h"
#include "interface/i_render_pass.h"

namespace tigine { namespace rhi {
class GL430RenderPass : public IRenderPass {
public:
    GL430RenderPass(const RenderPassDesc &desc) {}
    ~GL430RenderPass() = default;

private:
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_GL430_GL430_RENDER_PASS_H_
