#include "rhi.h"

#include <iostream>

#include "shader/rotate_texture_vert.h"
#include "shader/rotate_texture_frag.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace tigine::rhi;
using namespace std;

int main() {
    IRenderSystem *render = CREATE_RENDER_SYSTEM();

    RenderContextDesc context_desc {context_desc.resolution = {600, 600}};
    IRenderContext   *context = render->createRenderContext(context_desc);
    ISurface         *window  = context->getSurface();
    window->setTitle("rotate texture");
    window->show();

    float vertices[] = {0.5, -0.5f, 0, 1.0, 0.5, 0.5f, 1.0, 1.0, -0.5, 0.5f, 1.0, 0.0, -0.5, -0.5f, 0, 0};
    uint16_t indices[] = {0,1,2,0,2,3};

    BufferDesc vertices_buffer_desc;
    vertices_buffer_desc.kind     = BufferKind::Vertices;
    vertices_buffer_desc.buffer_size = sizeof(vertices);
    vertices_buffer_desc.data_desc.buffer_size = sizeof(vertices);
    vertices_buffer_desc.data_desc.data        = vertices;
    IBuffer *vertices_buffer = render->createBuffer(vertices_buffer_desc);

    BufferDesc indices_buffer_desc;
    indices_buffer_desc.kind      = BufferKind::Indices;
    indices_buffer_desc.buffer_size = sizeof(indices);
    indices_buffer_desc.data_desc.buffer_size = sizeof(indices);
    indices_buffer_desc.data_desc.data        = indices;
    IBuffer *indices_buffer = render->createBuffer(indices_buffer_desc);

    std::vector<BindingInfo> bindings_info(1);
    bindings_info[0].binding = 0;
    bindings_info[0].stride  = sizeof(vertices[0]) * 4;

    std::vector<AttributeInfo> attributes_info(2);
    attributes_info[0].binding  = 0;
    attributes_info[0].format   = DataFormat::RG32Float;
    attributes_info[0].location = 0;
    attributes_info[0].offset   = 0;
    attributes_info[1].binding  = 0;
    attributes_info[1].format   = DataFormat::RG32Float;
    attributes_info[1].location = 1;
    attributes_info[1].offset   = sizeof(vertices[0]) * 2;

    BufferArrayDesc array_desc;
    array_desc.vertices_buffer = vertices_buffer;
    array_desc.indices_buffer  = indices_buffer;
    array_desc.index_kind      = IndexKind::IK_UINT16;
    array_desc.bindings        = bindings_info;
    array_desc.attributes      = attributes_info;
    IBufferArray *vertices_array = render->createBufferArray(array_desc);

    ShaderDesc vert_shader_desc;
    vert_shader_desc.kind      = ShaderKind::Vertex;
    vert_shader_desc.code_size = rotate_texture_vert.size();
    vert_shader_desc.code      = rotate_texture_vert.data();
    IShader *vert_shader = render->createShader(vert_shader_desc);
    if (vert_shader->hasError()) std::cout << vert_shader->getReport() << std::endl;

    ShaderDesc frag_shader_desc;
    frag_shader_desc.kind      = ShaderKind::Fragment;
    frag_shader_desc.code_size = rotate_texture_frag.size();
    frag_shader_desc.code      = rotate_texture_frag.data();
    IShader *frag_shader = render->createShader(frag_shader_desc);
    if (frag_shader->hasError()) std::cout << frag_shader->getReport() << std::endl;

    ShaderProgramDesc shader_prog_desc;
    shader_prog_desc.vertex_shader   = vert_shader;
    shader_prog_desc.fragment_shader = frag_shader;
    IShaderProgram *shader_prog = render->createShaderProgram(shader_prog_desc);
    if (shader_prog->hasError()) std::cout << shader_prog->getReport() << std::endl;


    BufferDesc angle_buffer_desc;
    angle_buffer_desc.kind         = BufferKind::Vertices;
    angle_buffer_desc.buffer_size    = sizeof(float);
    IBuffer *angle_buffer = render->createBuffer(angle_buffer_desc);

    int      tex_width, tex_height, tex_channels;
    stbi_uc *pixels = stbi_load("E:/A.jpg", &tex_width, &tex_height, &tex_channels, STBI_rgb_alpha);
    TextureDesc texture_desc;
    texture_desc.kind = TextureKind::Texture2D;
    texture_desc.format = DataFormat::RGBA8UNorm_sRGB;
    texture_desc.texture_size.width = tex_width;
    texture_desc.texture_size.height = tex_height;
    texture_desc.data_desc.format    = DataFormat::RGBA8UNorm_sRGB;
    texture_desc.data_desc.texture_size.width = tex_width;
    texture_desc.data_desc.texture_size.height = tex_height;
    texture_desc.data_desc.data                = pixels;
    ITexture *texture   = render->createTexture(texture_desc);
    stbi_image_free(pixels);

    ResourceHeapDesc resource_heap_desc;
    resource_heap_desc.uniforms.resize(2);
    resource_heap_desc.uniforms[0].binding = 0;
    resource_heap_desc.uniforms[0].resource = angle_buffer;
    resource_heap_desc.uniforms[0].shader_stage = ShaderKind::Vertex;
    resource_heap_desc.uniforms[1].binding      = 1;
    resource_heap_desc.uniforms[1].resource     = texture;
    resource_heap_desc.uniforms[1].shader_stage = ShaderKind::Fragment;
    IResourceHeap *resource_heap = render->CreateResourceHeap(resource_heap_desc);

    PipelineStateDesc pipeline_desc;
    pipeline_desc.vertices_array = vertices_array;
    pipeline_desc.shader_program = shader_prog;
    pipeline_desc.resource_heap  = resource_heap;
    pipeline_desc.render_pass = context->getRenderPass();

    IPipelineState *pipeline = render->createPipelineState(pipeline_desc);

    ICommandQueue *queue = render->getCommandQueue();

    CommandBufferDesc command_buffer_desc;
    ICommandBuffer   *command_buffer = render->createCommandBuffer(command_buffer_desc);

#ifndef M_PI
#define M_PI 3.1415926
#endif // !M_PI
    float angle = 0;
    BufferDataDesc uniform_data_desc;
    uniform_data_desc.buffer_size = sizeof(angle);
    uniform_data_desc.data        = &angle;

    while (window->processEvents()) {
        angle += 0.0001;
        if (angle > 2 * M_PI) {
            angle -= 2 * M_PI;
        }
        angle_buffer->updateData(uniform_data_desc);

        command_buffer->begin();
        {
            command_buffer->setViewport({0, 0, context->getResolution().width, context->getResolution().height});
            command_buffer->setPipeState(pipeline);
            command_buffer->setVertexBufferArray(vertices_array);
            command_buffer->beginRenderPass(context);
            {
                command_buffer->clear(CF_Color);
                command_buffer->drawArray(6, 0);
            }
            command_buffer->endRenderPass();
        }
        command_buffer->end();

        queue->submit(command_buffer);

        context->present();
    }
}