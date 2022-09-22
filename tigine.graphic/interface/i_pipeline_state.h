#ifndef TIGINE_GRAPHIC_INTERFACE_I_PIPELINE_STATE_H_
#define TIGINE_GRAPHIC_INTERFACE_I_PIPELINE_STATE_H_

#include "interface/i_common.h"
#include "interface/i_render_pass.h"
#include "interface/i_shader_program.h"

namespace tigine { namespace graphic {
struct PipelineStateDescriptor {
    IShaderProgram *shader_program;
    IRenderPass    *render_pass;
    DrawMode        draw_mode = DrawMode::Triangles;
    ClearValue      clear_value;
};

class IPipelineState {
public:
    IPipelineState(const PipelineStateDescriptor &desc) : desc_(desc) {}
    virtual ~IPipelineState() = 0 {}

    IShaderProgram *getShaderProgram() const { return desc_.shader_program; }
    IRenderPass    *getRenderPass() const { return desc_.render_pass; }
    DrawMode        getDrawMode() const { return desc_.draw_mode; }
    ClearValue      getClearValue() const { return desc_.clear_value; }

private:
    PipelineStateDescriptor desc_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_PIPELINE_STATE_H_
