#include "graphic.h"

#include <iostream>

#include "hello_triangle_vert.h"
#include "hello_triangle_frag.h"

using namespace tigine::graphic;
using namespace std;

int main() {
    IRenderSystem *render = CREATE_RENDER_SYSTEM();

    RenderContextDescriptor context_desc {context_desc.resolution = {600, 600}};
    IRenderContext         *context = render->createRenderContext(context_desc);
    ISurface               *window  = context->getSurface();
    window->setTitle("test");
    window->show();



    float vertices[] = {0, 0.5f, 0, 0, 0, 1, 0.5f, -0.5f, 0, 1, 0, 0, -0.5f, -0.5f, 0, 0, 1, 0};

    BufferDescriptor buffer_desc;
    buffer_desc.kinds     = BK_Vertices;
    buffer_desc.data_size = sizeof(vertices);
    buffer_desc.data      = vertices;

    IBuffer *vertices_buffer = render->createBuffer(buffer_desc);

    std::vector<BindingInfo> bindings_info(1);
    bindings_info[0].binding = 0;
    bindings_info[0].stride  = sizeof(vertices[0]) * 6;

    std::vector<AttributeInfo> attributes_info(2);
    attributes_info[0].binding  = 0;
    attributes_info[0].format   = DF_RGB32Float;
    attributes_info[0].location = 0;
    attributes_info[0].offset   = 0;
    attributes_info[1].binding  = 0;
    attributes_info[1].format   = DF_RGB32Float;
    attributes_info[1].location = 1;
    attributes_info[1].offset   = sizeof(vertices[0]) * 3;

    BufferArrayDescriptor array_desc;
    array_desc.vertices_buffer  = vertices_buffer;
    array_desc.bindings_count   = bindings_info.size();
    array_desc.bindings         = bindings_info.data();
    array_desc.attributes_count = attributes_info.size();
    array_desc.attributes       = attributes_info.data();

    IBufferArray *vertices_array = render->createBufferArray(array_desc);



    ShaderDescriptor vert_shader_desc;
    vert_shader_desc.kind      = ShaderKind::Vertex;
    vert_shader_desc.code_size = hello_triangle_vert.size();
    vert_shader_desc.code      = hello_triangle_vert.data();

    IShader *vert_shader = render->createShader(vert_shader_desc);
    if (vert_shader->hasError()) std::cout << vert_shader->getReport() << std::endl;

    ShaderDescriptor frag_shader_desc;
    frag_shader_desc.kind      = ShaderKind::Fragment;
    frag_shader_desc.code_size = hello_triangle_frag.size();
    frag_shader_desc.code      = hello_triangle_frag.data();

    IShader *frag_shader = render->createShader(frag_shader_desc);
    if (frag_shader->hasError()) std::cout << frag_shader->getReport() << std::endl;

    ShaderProgramDescriptor shader_prog_desc;
    shader_prog_desc.vertex_shader = vert_shader;
    shader_prog_desc.fragment_shader = frag_shader;

    IShaderProgram *shader_prog = render->createShaderProgram(shader_prog_desc);



    ResourceHeapDescriptor resource_heap_desc;
    resource_heap_desc.uniforms_count = 0;
    resource_heap_desc.uniforms       = nullptr;

    IResourceHeap *resource_heap = render->CreateResourceHeap(resource_heap_desc);



    PipelineStateDescriptor pipeline_desc;
    pipeline_desc.vertices_array = vertices_array;
    pipeline_desc.shader_program = shader_prog;
    pipeline_desc.resource_heap  = resource_heap;
    pipeline_desc.render_pass    = context->getRenderPass();

    IPipelineState *pipeline = render->createPipelineState(pipeline_desc);


    ICommandQueue *queue = render->getCommandQueue();


    CommandBufferDescriptor command_buffer_desc;
    ICommandBuffer         *command_buffer = render->createCommandBuffer(command_buffer_desc);

    //    string sky_vertex_shader = R"delimiter(
//#version 330 core
//layout(location = 0) in vec3 pos;
//layout(location = 1) in vec3 color;
//
//out vec4 ucolor;
//
//void main() {
//	ucolor = vec4(color, 1.0);
//    gl_Position = vec4(pos, 1.0);
//}
//)delimiter";
//
//    string sky_fragment_shader = R"delimiter(
//#version 330 core
//in vec4 ucolor;
//
//layout(location = 0) out vec4 out_color;
//
//void main() {
//    out_color = ucolor;
//}
//)delimiter";
//
//    ShaderDescriptor vert_desc {vert_desc.kind = ShaderKind::Vertex, vert_desc.code = sky_vertex_shader.data()};
//    IShader         *vert_shader = render->createShader(vert_desc);
//    if (vert_shader->hasError()) {
//        std::cout << vert_shader->getReport() << std::endl;
//    }
//
//    ShaderDescriptor frag_desc {frag_desc.kind = ShaderKind::Fragment, frag_desc.code = sky_fragment_shader.data()};
//    IShader         *frag_shader = render->createShader(frag_desc);
//    if (frag_shader->hasError()) {
//        std::cout << frag_shader->getReport() << std::endl;
//    }
//
//    ShaderProgramDescriptor prog_desc {prog_desc.vertex_shader = vert_shader, prog_desc.fragment_shader = frag_shader};
//
//    IShaderProgram *prog = render->createShaderProgram(prog_desc);
//    if (prog->hasError()) {
//        std::cout << prog->getReport() << std::endl;
//    }
//
//    float            vertices[] = {0, 0.5f, 0, 0, 0, 1, 0.5f, -0.5f, 0, 1, 0, 0, -0.5f, -0.5f, 0, 0, 1, 0};
//    BufferDescriptor buffer_desc {buffer_desc.size = sizeof(float) * 18, buffer_desc.kinds = BK_Vertices};
//    IBuffer         *vetices_buffer = render->createBuffer(buffer_desc, vertices);
//
//    VertexAttribute       pos_attribute {DF_RGB32Float, 0, 0, sizeof(float) * 6};
//    VertexAttribute       color_attribute {DF_RGB32Float, 1, sizeof(float) * 3, sizeof(float) * 6};
//    BufferArrayDescriptor array_buffer_desc;
//    {
//        array_buffer_desc.vertices_buffer   = vetices_buffer;
//        array_buffer_desc.indices_buffer    = nullptr;
//        array_buffer_desc.vertex_attributes = {pos_attribute, color_attribute};
//    }
//    IBufferArray *array_buffer = render->createBufferArray(array_buffer_desc);
//
//    PipelineStateDescriptor pipeline_desc;
//    {
//        pipeline_desc.shader_program = prog;
//        pipeline_desc.render_pass    = context->getRenderPass();
//    }
//    IPipelineState *pipeline_state = render->createPipelineState(pipeline_desc);
//
//    ICommandQueue  *queue          = render->getCommandQueue();
//    ICommandBuffer *command_buffer = render->createCommandBuffer();
//
    while (window->processEvents()) {
//        command_buffer->begin();
//        command_buffer->setViewport({0, 0, context->getResolution().width, context->getResolution().height});
//        command_buffer->setPipeState(pipeline_state);
//        command_buffer->setVertexBufferArray(array_buffer);
//        command_buffer->beginRenderPass(context->getRenderPass());
//        command_buffer->clear(CF_Color);
//        command_buffer->drawArray(3, 0);
//        command_buffer->endRenderPass();
//        command_buffer->end();
//        queue->submit(command_buffer);
//        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);clang
//        // glClear(GL_COLOR_BUFFER_BIT);
//        // glUseProgram(prog->getID());
//        // glBindVertexArray(array_buffer->getID());
//        // glDrawArrays(GL_TRIANGLES, 0, 3);
        context->present();
    }
}