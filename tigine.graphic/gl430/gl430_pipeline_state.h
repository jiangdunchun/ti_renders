#ifndef TIGINE_GRAPHIC_GL430_GL430_PIPELINE_STATE_H_
#define TIGINE_GRAPHIC_GL430_GL430_PIPELINE_STATE_H_

#include "gl430/gl430_common.h"
#include "gl430/gl430_shader_program.h"
#include "gl430/gl430_render_pass.h"

namespace tigine {
namespace graphic {
struct PipelineDescriptor {
	GL430ShaderProgram* shader_program;
	GL430RenderPass* render_pass;
};

class GL430PipelineState {
public:
	GL430PipelineState(const PipelineDescriptor& desc) : desc_(desc_){}
	~GL430PipelineState() = default;
    DISALLOW_COPY_AND_ASSIGN(GL430PipelineState);

private:
	PipelineDescriptor desc_;
};
} // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_GL430_GL430_PIPELINE_STATE_H_
