#ifndef TIGINE_GRAPHIC_GL430_GL430_PIPELINE_STATE_H_
#define TIGINE_GRAPHIC_GL430_GL430_PIPELINE_STATE_H_

#include "gl430/gl430_common.h"
#include "gl430/gl430_shader_program.h"
#include "gl430/gl430_render_pass.h"
#include "interface/i_pipeline_state.h"

namespace tigine { namespace graphic {
class GL430PipelineState : public IPipelineState {
public:
    GL430PipelineState(const PipelineStateDesc &desc) { 
        shader_program_ = dynamic_cast<GL430ShaderProgram *>(desc.shader_program);
        render_pass_    = dynamic_cast<GL430RenderPass *>(desc.render_pass);
        draw_mode_      = desc.draw_mode;
        clear_value_    = desc.clear_value;
    }
    ~GL430PipelineState() = default;

    GL430ShaderProgram *getShaderProgram() const { return shader_program_; }
    GL430RenderPass    *getRenderPass() const { return render_pass_; }
    DrawMode            getDrawMode() const { return draw_mode_; }
    ClearValue          getClearValue() const { return clear_value_; }

private:
    GL430ShaderProgram *shader_program_;
    GL430RenderPass    *render_pass_;
    DrawMode            draw_mode_;
    ClearValue          clear_value_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_GL430_GL430_PIPELINE_STATE_H_
