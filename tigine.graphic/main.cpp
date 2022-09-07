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
layout(location = 0) in vec3 aPosition;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
    vec4 position = uProjection * uView * uModel * vec4(aPosition, 1.0f);
    gl_Position = position + vec4(0.0f, 0.0f, 0.00001f, 0.0f);
}
)delimiter";

	string sky_fragment_shader = R"delimiter(
#version 330 core
uniform vec4 uID;

layout(location = 0) out vec4 fID;

void main() {
    fID = uID;
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

	while (window->is_active()) {
	}
}