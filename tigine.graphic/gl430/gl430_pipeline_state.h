#ifndef TIGINE_GRAPHIC_GL430_GL430_PIPELINE_STATE_H_
#define TIGINE_GRAPHIC_GL430_GL430_PIPELINE_STATE_H_

#include "gl430/gl430_common.h"
#include "gl430/gl430_shader_program.h"
#include "gl430/gl430_render_pass.h"

namespace tigine { namespace graphic {
struct PipelineStateDescriptor {
    GL430ShaderProgram *shader_program;
    GL430RenderPass    *render_pass;
    DrawMode            draw_mode = DrawMode::Triangles;
    ClearValue          clear_value;
};

class GL430CommandBuffer;
class GL430PipelineState {
public:
    GL430PipelineState(const PipelineStateDescriptor &desc) : desc_(desc) {}
    ~GL430PipelineState() = default;
    DISALLOW_COPY_AND_ASSIGN(GL430PipelineState);

private:
    friend class GL430CommandBuffer;
    PipelineStateDescriptor desc_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_GL430_GL430_PIPELINE_STATE_H_
