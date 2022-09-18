#ifndef TIGINE_GRAPHIC_GL430_GL430_RENDER_SYSTEM_H_
#define TIGINE_GRAPHIC_GL430_GL430_RENDER_SYSTEM_H_

#include "gl430/gl430_render_context.h"
#include "gl430/gl430_shader.h"
#include "gl430/gl430_shader_program.h"
#include "gl430/gl430_buffer.h"
#include "gl430/gl430_buffer_array.h"
#include "gl430/gl430_command_queue.h"
#include "gl430/gl430_command_buffer.h"
#include "gl430/gl430_pipeline_state.h"

namespace tigine {
namespace graphic {
class GL430RenderSystem {
public:
    GL430RenderSystem() {
        command_queue_ = new GL430CommandQueue();
    }
    ~GL430RenderSystem() {
        delete command_queue_;
    }
    DISALLOW_COPY_AND_ASSIGN(GL430RenderSystem);

    GL430RenderContext* createRenderContext(const RenderContextDescriptor& desc) {
        return new GL430RenderContext(desc);
    }
    void release(GL430RenderContext* render_context) {
        delete render_context; 
    }
    GL430Shader* createShader(const ShaderDescriptor& desc) {
        return new GL430Shader(desc);
    }
    void release(GL430Shader* shader) {
        delete shader; 
    }
    GL430ShaderProgram* createShaderProgram(const ShaderProgramDescriptor& desc) { 
        return new GL430ShaderProgram(desc);
    }
    void release(GL430ShaderProgram* shader_program) {
        delete shader_program;
    }
    GL430Buffer* createBuffer(const BufferDescriptor& desc, void* data) {
        return new GL430Buffer(desc, data); 
    }
    void release(GL430Buffer* buffer) {
        delete buffer; 
    }
    GL430BufferArray* createBufferArray(const BufferArrayDescriptor& desc) {
        return new GL430BufferArray(desc);
    }
    void release(GL430BufferArray* buffer_array) { 
        delete buffer_array; 
    }
    GL430CommandQueue* getCommandQueue() {
        return command_queue_;
    }
    GL430CommandBuffer* createCommandBuffer() {
        return new GL430CommandBuffer();
    }
    void release(GL430CommandBuffer* command_buffer) {
        delete command_buffer;
    }
    GL430PipelineState* createPipeline(const PipelineDescriptor& desc) {
        return new GL430PipelineState(desc);
    }
    void release(GL430PipelineState* pipeline) {
        delete pipeline;
    }

private:
    GL430CommandQueue* command_queue_ = nullptr;
};
} // // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_GL430_GL430_RENDER_SYSTEM_H_
