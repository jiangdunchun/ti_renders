#include "emissive_pass.h"

#include "../file/shader_file.h"

using namespace std;
using namespace glm;

namespace ti_render {
	emissive_pass::emissive_pass(unsigned int width, unsigned int height, texture_2d* emissive) {
		shader_file s_file(m_shader_path);
		m_shader = new shader(s_file.get_vertex_code(), s_file.get_fragment_code());

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

		m_emissive_h = new texture_2d(width / 2, height / 2, color_format::RGB16F);
		m_emissive_v = new texture_2d(width / 2, height / 2, color_format::RGB16F);
		m_frame_buffer = new frame_buffer(width / 2, height / 2);
	}

	emissive_pass::~emissive_pass() {
		delete m_shader;
		delete m_mesh;
		delete m_emissive_h;
		delete m_emissive_v;
		delete m_frame_buffer;
	}

	void emissive_pass::rend(render_system* render) {
		m_frame_buffer->bind();
		render->set_clear_color(vec4(0.0f, 0.0f, 0.0f, 0.0f));
		render->set(graphic_capability::DEPTH_TEST, true);
		render->set(graphic_func::DEPTH_MASK, true);
		render->set_depth_func(depth_func::LESS);

		int is_horizontal;

		is_horizontal = 1;
		m_frame_buffer->attach_color_buffer(0, m_emissive_h);
		render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);
		m_shader->use();
		m_shader->set_texture_2d("uEmissive", *m_emissive_in);
		m_shader->set_int("uHorizontal", is_horizontal);
		m_mesh->draw();

		is_horizontal = 0;
		m_frame_buffer->attach_color_buffer(0, m_emissive_v);
		render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);
		m_shader->use();
		m_shader->set_texture_2d("uEmissive", *m_emissive_h);
		m_shader->set_int("uHorizontal", is_horizontal);
		m_mesh->draw();

		for (unsigned int i = 0; i < 1; i++) {
			is_horizontal = 1;
			m_frame_buffer->attach_color_buffer(0, m_emissive_h);
			render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);
			m_shader->use();
			m_shader->set_texture_2d("uEmissive", *m_emissive_v);
			m_shader->set_int("uHorizontal", is_horizontal);
			m_mesh->draw();

			is_horizontal = 0;
			m_frame_buffer->attach_color_buffer(0, m_emissive_v);
			render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);
			m_shader->use();
			m_shader->set_texture_2d("uEmissive", *m_emissive_h);
			m_shader->set_int("uHorizontal", is_horizontal);
			m_mesh->draw();
		}
	}
}