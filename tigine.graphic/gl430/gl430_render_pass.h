#ifndef TIGINE_GRAPHIC_GL430_GL430_RENDER_PASS_H_
#define TIGINE_GRAPHIC_GL430_GL430_RENDER_PASS_H_

#include "gl430/gl430_common.h"
#include "interface/i_render_pass.h"

namespace tigine { namespace graphic {
class GL430RenderPass : public IRenderPass {
public:
    GL430RenderPass(const RenderPassDescriptor &desc) {}
    ~GL430RenderPass() = default;

private:
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_GL430_GL430_RENDER_PASS_H_
