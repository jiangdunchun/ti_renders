#include "water_pass.h"

#include "../file/shader_file.h"

using namespace glm;
using namespace std;

namespace ti_render {
	water_pass::water_pass(
		unsigned int width,
		unsigned int height,
		texture_2d* position,
		texture_2d* base_color,
		ds_render_buffer* ds_buffer) {
		shader_file s_file(m_shader_path);
		m_shader = new shader(s_file.get_vertex_code(), s_file.get_fragment_code());

		m_position_in = position;
		m_base_color_in = base_color;

		m_color = new texture_2d(width, height, color_format::RGBA16F);
		m_frame_buffer = new frame_buffer(width, height, ds_buffer);
		m_frame_buffer->attach_color_buffer(0, m_color);
	}

	water_pass::~water_pass() {
		delete m_shader;
		delete m_color;
		delete m_frame_buffer;
	}
	void water_pass::rend(
		render_system* render,
		camera_object* camera,
		sky_object* sky,
		vector<water_object*> waters) {
		m_frame_buffer->bind();
		render->set_clear_color(vec4(0.0f, 0.0f, 0.0f, 0.0f));
		render->set(graphic_capability::DEPTH_TEST, true);
		render->set(graphic_func::DEPTH_MASK, true);
		render->set_depth_func(depth_func::LESS);
		render->clear_frame_buffer(frame_buffer_type::COLOR);

		m_shader->use();
		m_shader->set_mat4("uProjection", camera->get_projection());
		m_shader->set_mat4("uView", camera->get_view());
		m_shader->set_vec3("uView_position", camera->get_world_position());
		m_shader->set_vec2("uScreen", vec2(m_color->get_width(), m_color->get_height()));
		m_shader->set_texture_2d("uPosition", *m_position_in);
		m_shader->set_texture_2d("uBase_color", *m_base_color_in);
		m_shader->set_texture_cube("uEnvironment", *sky->m_environment_cube);
		for (vector<water_object*>::iterator w_iter = waters.begin();
			w_iter != waters.end();
			++w_iter) {
			m_shader->set_mat4("uModel", (*w_iter)->get_world_transform());
			for (int i = 0; i < (*w_iter)->m_mesh->m_vbo_buffer.size(); ++i) {
				(*w_iter)->m_mesh->m_vbo_buffer[i]->draw();
			}
		}
	}
}