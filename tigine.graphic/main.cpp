#include "gl430/gl430_render_system.h"

#include <iostream>

using namespace tigine::graphic;
using namespace std;

void test_shader(GL430RenderSystem& render) {
	string test_vertex_shader = R"delimiter(
#version 430 core
layout(location = 0) in vec3 aPosition;

out VS_OUT{
    vec3 tex_coord;
} vs_out;

layout(location = 0) uniform mat4 uProjection;
layout(location = 1) uniform mat4 uView;

void main() {
    vs_out.tex_coord = normalize(aPosition);
    gl_Position = uProjection * uView * vec4(aPosition, 1.0f);
}
)delimiter";

	string test_fragment_shader = R"delimiter(
#version 430 core
in VS_OUT{
    vec3 tex_coord;
} fs_in;

layout(location = 2) uniform samplerCube uEnvironment;

layout(location = 0) out vec3 fBackgroud;

void main() {
    fBackgroud = texture(uEnvironment, normalize(fs_in.tex_coord)).rgb;
}
)delimiter";

	ShaderDescriptor vert_desc{
		vert_desc.kind = ShaderKind::Vertex,
		vert_desc.code = test_vertex_shader.data()
	};
	GL430Shader* vert_shader = render.createShader(vert_desc);
	if (vert_shader->hasError()) {
		std::cout << vert_shader->getReport() << std::endl;
	}

	ShaderDescriptor frag_desc {
		frag_desc.kind = ShaderKind::Fragment,
		frag_desc.code = test_fragment_shader.data()
	};
	GL430Shader* frag_shader = render.createShader(frag_desc);
	if (frag_shader->hasError()) {
		std::cout << frag_shader->getReport() << std::endl;
	}

	ShaderProgramDescriptor prog_desc{
		prog_desc.vertex_shader = vert_shader,
		prog_desc.fragment_shader = frag_shader
	};

	GL430ShaderProgram* prog = render.createShaderProgram(prog_desc);
	if (prog->hasError()) {
		std::cout << prog->getReport() << std::endl;
	}
}


int main() {
	GL430RenderSystem render;
	RenderContextDescriptor context_desc{
        context_desc.width = 600,
        context_desc.height = 600,
	};
    GL430RenderContext* context = render.createRenderContext(context_desc);
    GL430Surface*  window  = context->surface();
	window->setTitle("test");
	window->show();

	test_shader(render);

	string sky_vertex_shader = R"delimiter(
#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

out vec4 ucolor;

void main() {
	ucolor = vec4(color, 1.0);
    gl_Position = vec4(pos, 1.0);
}
)delimiter";

	string sky_fragment_shader = R"delimiter(
#version 330 core
in vec4 ucolor;

layout(location = 0) out vec4 out_color;

void main() {
    out_color = ucolor;
}
)delimiter";

	ShaderDescriptor vert_desc{
		vert_desc.kind = ShaderKind::Vertex,
		vert_desc.code = sky_vertex_shader.data()
	};
	GL430Shader* vert_shader = render.createShader(vert_desc);
	if (vert_shader->hasError()) {
		std::cout << vert_shader->getReport() << std::endl;
	}

	ShaderDescriptor frag_desc {
		frag_desc.kind = ShaderKind::Fragment,
		frag_desc.code = sky_fragment_shader.data()
	};
	GL430Shader* frag_shader = render.createShader(frag_desc);
	if (frag_shader->hasError()) {
		std::cout << frag_shader->getReport() << std::endl;
	}

	ShaderProgramDescriptor prog_desc{
		prog_desc.vertex_shader = vert_shader,
		prog_desc.fragment_shader = frag_shader
	};

	GL430ShaderProgram* prog = render.createShaderProgram(prog_desc);
	if (prog->hasError()) {
		std::cout << prog->getReport() << std::endl;
	}

	float vertices[] = {
		0,  0.5f, 0, 0, 0, 1,
		0.5f, -0.5f, 0, 1, 0, 0,
		-0.5f, -0.5f, 0, 0, 1, 0
	};
	BufferDescriptor buffer_desc{
		buffer_desc.size = sizeof(float) * 18,
		buffer_desc.kinds = BK_Array
	};
	GL430Buffer* vetices_buffer = render.createBuffer(buffer_desc, vertices);

	VertexAttribute pos_attribute{
		DF_RGB32Float, 0, 0, sizeof(float) * 6
	};
	VertexAttribute color_attribute{
		DF_RGB32Float, 1, sizeof(float) * 3, sizeof(float) * 6
	};
	BufferArrayDescriptor array_buffer_desc; {
		array_buffer_desc.vertices_buffer = vetices_buffer;
		array_buffer_desc.indices_buffer = nullptr;
		array_buffer_desc.vertex_attributes = { pos_attribute, color_attribute };

	}
	GL430BufferArray* array_buffer = render.createBufferArray(array_buffer_desc);

	while (window->processEvents()) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(prog->id());
		glBindVertexArray(array_buffer->id());
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window->present();
	}
}