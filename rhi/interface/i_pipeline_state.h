#ifndef TIGINE_RHI_INTERFACE_I_PIPELINE_STATE_H_
#define TIGINE_RHI_INTERFACE_I_PIPELINE_STATE_H_

#include "interface/i_common.h"
#include "interface/i_render_pass.h"
#include "interface/i_shader_program.h"
#include "interface/i_resource_heap.h"
#include "interface/i_buffer_array.h"

namespace tigine { namespace rhi {
struct PipelineStateDesc {
    IShaderProgram  *shader_program;
    IResourceHeap   *resource_heap;
    IBufferArray    *vertices_array;
    IRenderPass     *render_pass;
    DrawMode         draw_mode = DrawMode::Triangles;
    ClearValue       clear_value;
};

class IPipelineState : public NonCopyable {
public:
    ClearValue get_clear_value() const { return clear_value_; }

protected:
    ClearValue clear_value_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_PIPELINE_STATE_H_
