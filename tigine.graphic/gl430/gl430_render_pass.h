#ifndef TIGINE_GRAPHIC_GL430_GL430_RENDER_PASS_H_
#define TIGINE_GRAPHIC_GL430_GL430_RENDER_PASS_H_

#include "gl430/gl430_common.h"

namespace tigine {
namespace graphic {
struct RenderPassDescriptor {
	
};

class GL430RenderPass {
public:
	GL430RenderPass(const RenderPassDescriptor& desc) {}
	~GL430RenderPass() = default;
    DISALLOW_COPY_AND_ASSIGN(GL430RenderPass);

private:
};
} // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_GL430_GL430_RENDER_PASS_H_
