#ifndef TIGINE_GRAPHIC_INTERFACE_I_PIPELINE_STATE_H_
#define TIGINE_GRAPHIC_INTERFACE_I_PIPELINE_STATE_H_

#include "interface/i_common.h"
#include "interface/i_render_pass.h"
#include "interface/i_shader_program.h"
#include "interface/i_resource_heap.h"
#include "interface/i_buffer_array.h"

namespace tigine { namespace graphic {
struct PipelineStateDescriptor {
    IShaderProgram  *shader_program;
    IResourceHeap   *resource_heap;
    IBufferArray    *vertices_array;
    IRenderPass     *render_pass;
    DrawMode         draw_mode = DrawMode::Triangles;
    ClearValue       clear_value;
};

class IPipelineState : public NonCopyable {};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_PIPELINE_STATE_H_
