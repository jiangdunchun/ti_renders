#include "light_pass.h"

#include "../file/shader_file.h"
#include "../file/image_file.h"

using namespace glm;
using namespace std;

namespace ti_render {
	light_pass::light_pass(
		unsigned int width,
		unsigned int height,
		texture_2d* position,
		texture_2d* base_color,
		texture_2d* normal,
		texture_2d* material) {
		shader_file s_file(m_shader_path);
		m_shader = new shader(s_file.get_vertex_code(), s_file.get_fragment_code());

		image_file i_file(m_lut_path, color_format::RGB8B, true);
		m_lut = new texture_2d(i_file.get_width(), i_file.get_height(), color_format::RGB8B);
		m_lut->push_data(i_file.get_color_format(), i_file.get_data());

		m_position_in = position;
		m_base_color_in = base_color;
		m_normal_in = normal;
		m_material_in = material;

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

		m_color = new texture_2d(width, height, color_format::RGBA8B);
		m_frame_buffer = new frame_buffer(width, height);
		m_frame_buffer->attach_color_buffer(0, m_color);
	}

	light_pass::~light_pass() {
		delete m_shader;
		delete m_lut;
		delete m_mesh;
		delete m_color;
		delete m_frame_buffer;
	}

	void light_pass::rend(
		render_system* render,
		camera_object* camera,
		sky_object* sky,
		vector<light_object*> lights) {
		m_frame_buffer->bind();
		render->set_clear_color(vec4(0.0f, 0.0f, 0.0f, 0.0f));
		render->set(graphic_capability::DEPTH_TEST, true);
		render->set(graphic_func::DEPTH_MASK, true);
		render->set_depth_func(depth_func::LESS);
		render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);

		m_shader->use();

	}
}