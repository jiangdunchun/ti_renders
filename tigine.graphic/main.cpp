#include "gl430plus/gl430plus_render_system.h"

#include <iostream>

using namespace tigine;
using namespace std;

int main() {
	gl430plus_render_system render;
	render_context_descriptor cxt_dscp{
		cxt_dscp.width = 600,
		cxt_dscp.height = 600,
	};
	gl430plus_render_context* cxt = render.create_render_context(cxt_dscp);
	gl430plus_surface* window = cxt->get_surface();
	window->set_title("test");
	window->show();

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

	shader_descriptor vert_desc{
		vert_desc.type = shader_type::vertex,
		vert_desc.source = sky_vertex_shader.data()
	};
	gl430plus_shader* vert_shader = render.create_shader(vert_desc);
	if (vert_shader->has_error()) {
		std::cout << vert_shader->get_report() << std::endl;
	}

	shader_descriptor frag_desc{
		frag_desc.type = shader_type::fragment,
		frag_desc.source = sky_fragment_shader.data()
	};
	gl430plus_shader* frag_shader = render.create_shader(frag_desc);
	if (frag_shader->has_error()) {
		std::cout << frag_shader->get_report() << std::endl;
	}

	shader_program_descriptor prog_desc{
		prog_desc.vertex_shader = vert_shader,
		prog_desc.fragment_shader = frag_shader
	};

	gl430plus_shader_program* prog = render.create_shader_program(prog_desc);
	if (prog->has_error()) {
		std::cout << prog->get_report() << std::endl;
	}

	float vertices[] = {
		0,  0.5f, 0, 0, 0, 1,
		0.5f, -0.5f, 0, 1, 0, 0,
		-0.5f, -0.5f, 0, 0, 1, 0
	};
	buffer_descriptor buffer_desc{
		buffer_desc.size = sizeof(float) * 18,
		buffer_desc.flags = ARRAY_BUFFER
	};
	gl430plus_buffer* vetices_buffer = render.create_buffer(buffer_desc, vertices);

	vertex_attribute pos_attribute{
		"position", RGB32Float, 0, 0, sizeof(float) * 6
	};
	vertex_attribute color_attribute{
		"color", RGB32Float, 1, sizeof(float) * 3, sizeof(float) * 6
	};
	buffer_array_descriptor array_buffer_desc; {
		array_buffer_desc.vertices_buffer = vetices_buffer;
		array_buffer_desc.indices_buffer = nullptr;
		array_buffer_desc.vertex_attributes = { pos_attribute, color_attribute };

	}
	gl430plus_buffer_array* array_buffer = render.create_buffer_array(array_buffer_desc);

	while (window->process_events()) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(prog->get_id());
		glBindVertexArray(array_buffer->get_id());
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window->present();
	}
}