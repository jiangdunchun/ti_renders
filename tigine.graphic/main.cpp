#include "graphic.h"

#include <iostream>

#include "hello_triangle_vert.h"
#include "hello_triangle_frag.h"

using namespace tigine::graphic;
using namespace std;

int main() {
    IRenderSystem *render = CREATE_RENDER_SYSTEM();

    RenderContextDesc context_desc {context_desc.resolution = {600, 600}};
    IRenderContext         *context = render->createRenderContext(context_desc);
    ISurface               *window  = context->getSurface();
    window->setTitle("test");
    window->show();



    float vertices[] = {0, -0.5f, 0, 0, 0, 1, 0.5f, 0.5f, 0, 1, 0, 0, -0.5f, 0.5f, 0, 0, 1, 0};

    BufferDesc buffer_desc;
    buffer_desc.kinds     = BK_Vertices;
    buffer_desc.data_size = sizeof(vertices);
    buffer_desc.data      = vertices;

    IBuffer *vertices_buffer = render->createBuffer(buffer_desc);

    std::vector<BindingInfo> bindings_info(1);
    bindings_info[0].binding = 0;
    bindings_info[0].stride  = sizeof(vertices[0]) * 6;

    std::vector<AttributeInfo> attributes_info(2);
    attributes_info[0].binding  = 0;
    attributes_info[0].format   = DataFormat::RGB32Float;
    attributes_info[0].location = 0;
    attributes_info[0].offset   = 0;
    attributes_info[1].binding  = 0;
    attributes_info[1].format   = DataFormat::RGB32Float;
    attributes_info[1].location = 1;
    attributes_info[1].offset   = sizeof(vertices[0]) * 3;

    BufferArrayDesc array_desc;
    array_desc.vertices_buffer  = vertices_buffer;
    array_desc.bindings_count   = bindings_info.size();
    array_desc.bindings         = bindings_info.data();
    array_desc.attributes_count = attributes_info.size();
    array_desc.attributes       = attributes_info.data();

    IBufferArray *vertices_array = render->createBufferArray(array_desc);



    ShaderDesc vert_shader_desc;
    vert_shader_desc.kind      = ShaderKind::Vertex;
    vert_shader_desc.code_size = hello_triangle_vert.size();
    vert_shader_desc.code      = hello_triangle_vert.data();

    IShader *vert_shader = render->createShader(vert_shader_desc);
    if (vert_shader->hasError()) std::cout << vert_shader->getReport() << std::endl;

    ShaderDesc frag_shader_desc;
    frag_shader_desc.kind      = ShaderKind::Fragment;
    frag_shader_desc.code_size = hello_triangle_frag.size();
    frag_shader_desc.code      = hello_triangle_frag.data();

    IShader *frag_shader = render->createShader(frag_shader_desc);
    if (frag_shader->hasError()) std::cout << frag_shader->getReport() << std::endl;

    ShaderProgramDesc shader_prog_desc;
    shader_prog_desc.vertex_shader = vert_shader;
    shader_prog_desc.fragment_shader = frag_shader;

    IShaderProgram *shader_prog = render->createShaderProgram(shader_prog_desc);



    ResourceHeapDesc resource_heap_desc;
    resource_heap_desc.uniforms_count = 0;
    resource_heap_desc.uniforms       = nullptr;

    IResourceHeap *resource_heap = render->CreateResourceHeap(resource_heap_desc);



    PipelineStateDesc pipeline_desc;
    pipeline_desc.vertices_array = vertices_array;
    pipeline_desc.shader_program = shader_prog;
    pipeline_desc.resource_heap  = resource_heap;
    //@TODO
    pipeline_desc.render_pass    = context->getRenderPass();

    IPipelineState *pipeline = render->createPipelineState(pipeline_desc);



    ICommandQueue *queue = render->getCommandQueue();



    CommandBufferDesc command_buffer_desc;
    ICommandBuffer         *command_buffer = render->createCommandBuffer(command_buffer_desc);



    while (window->processEvents()) {
        command_buffer->begin(); {
            command_buffer->setViewport({0, 0, context->getResolution().width, context->getResolution().height});
            command_buffer->setPipeState(pipeline);
            command_buffer->setVertexBufferArray(vertices_array);
            command_buffer->beginRenderPass(context, context->getRenderPass());
            {
                command_buffer->clear(CF_Color);
                command_buffer->drawArray(3, 0);
            }
            command_buffer->endRenderPass();
        }
        command_buffer->end();

        queue->submit(command_buffer);

        context->present();
    }
}