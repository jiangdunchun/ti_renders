#include "final_pass.h"

#include "../file/shader_file.h"

using namespace std;
using namespace glm;

namespace ti_render {
	final_pass::final_pass(
		unsigned int width,
		unsigned int height,
		texture_2d* color,
		texture_2d* water,
		texture_2d* background,
		texture_2d* emissive) : m_width(width), m_height(height) {
		shader_file s_file(m_shader_path);
		m_shader = new shader(s_file.get_vertex_code(), s_file.get_fragment_code());

		m_color_in = color;
		m_water_in = water;
		m_background_in = background;
		m_emissive_in = emissive;

		vector<vertex> vertices = {
			{vec3(-1.0f, -1.0f, 0.0f), vec2(0.0f, 0.0f)},
			{vec3(1.0f, -1.0f, 0.0f), vec2(1.0f, 0.0f)},
			{vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)},
			{vec3(-1.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)}
		};
		vector<unsigned int> indices = {
			0, 1, 3,
			1, 2, 3
		};
		m_mesh = new vertex_buffer(vertices, indices);
	}

	final_pass::~final_pass() {
		delete m_shader;
		delete m_mesh;
	}

	void final_pass::rend(render_system* render) {
		render->rend_to_screen();
		render->set_resolution(m_width, m_height);
		render->set_clear_color(vec4(0.0f, 0.0f, 0.0f, 0.0f));
		render->set(graphic_capability::DEPTH_TEST, true);
		render->set(graphic_func::DEPTH_MASK, true);
		render->set_depth_func(depth_func::LESS);
		render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);

		m_shader->use();
		m_shader->set_texture_2d("uColor", *m_color_in);
		m_shader->set_texture_2d("uWater", *m_water_in);
		m_shader->set_texture_2d("uBackground", *m_background_in);
		m_shader->set_texture_2d("uEmissive", *m_emissive_in);
		m_mesh->draw();
	}
}