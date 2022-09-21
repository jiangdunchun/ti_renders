#ifndef TIGINE_GRAPHIC_GL430_GL430_RENDER_SYSTEM_H_
#define TIGINE_GRAPHIC_GL430_GL430_RENDER_SYSTEM_H_

#include "interface/i_render_system.h"

#include "gl430/gl430_render_context.h"
#include "gl430/gl430_shader.h"
#include "gl430/gl430_shader_program.h"
#include "gl430/gl430_buffer.h"
#include "gl430/gl430_buffer_array.h"
#include "gl430/gl430_command_queue.h"
#include "gl430/gl430_command_buffer.h"
#include "gl430/gl430_pipeline_state.h"

namespace tigine { namespace graphic {
class GL430RenderSystem : public IRenderSystem {
public:
    GL430RenderSystem() { command_queue_ = new GL430CommandQueue(); }
    ~GL430RenderSystem() { delete command_queue_; }
    DISALLOW_COPY_AND_ASSIGN(GL430RenderSystem);

    IRenderContext *
        createRenderContext(const RenderContextDescriptor &desc) {
        return new GL430RenderContext(desc);
    }
    void release(IRenderContext *render_context) { delete render_context; }
    IShader *createShader(const ShaderDescriptor &desc) {
        return new GL430Shader(desc);
    }
    void release(IShader *shader) { delete shader; }
    IShaderProgram *
        createShaderProgram(const ShaderProgramDescriptor &desc) {
        return new GL430ShaderProgram(desc);
    }
    void release(IShaderProgram *shader_program) { delete shader_program; }
    IBuffer *createBuffer(const BufferDescriptor &desc, void *data) {
        return new GL430Buffer(desc, data);
    }
    void              release(IBuffer *buffer) { delete buffer; }
    IBufferArray *createBufferArray(const BufferArrayDescriptor &desc) {
        return new GL430BufferArray(desc);
    }
    void release(IBufferArray *buffer_array) { delete buffer_array; }
    ICommandQueue  *getCommandQueue() { return command_queue_; }
    ICommandBuffer *createCommandBuffer() {
        return new GL430CommandBuffer();
    }
    void release(ICommandBuffer *command_buffer) { delete command_buffer; }
    IPipelineState *createPipeline(const PipelineStateDescriptor &desc) {
        return new GL430PipelineState(desc);
    }
    void release(IPipelineState *pipeline) { delete pipeline; }

private:
    GL430CommandQueue *command_queue_ = nullptr;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_GL430_GL430_RENDER_SYSTEM_H_
