#include "pre_pass.h"

using namespace std;
using namespace glm;

namespace ti_render {
	glm::vec4 pre_pass::get_color(unsigned int id) {
		vec4 color;
		color.r = (id & 0xff) / float(0xff);
		id >>= 8;
		color.g = (id & 0xff) / float(0xff);
		id >>= 8;
		color.b = (id & 0xff) / float(0xff);
		id >>= 8;
		color.a = (id & 0xff) / float(0xff);
		return color;
	}

	pre_pass::pre_pass(unsigned int width, unsigned int height) {
		shader_file s_file(m_shader_path);
		m_shader = new shader(s_file.get_vertex_code(), s_file.get_fragment_code());
		m_id_texture = new texture_2d(width, height, color_format::RGBA8B);
		m_ds_render_buffer = new ds_render_buffer(width, height);
		m_frame_buffer = new frame_buffer(width, height, m_ds_render_buffer);
		m_frame_buffer->attach_color_buffer(0, m_id_texture);
	}

	pre_pass::~pre_pass() {
		delete m_shader;
		delete m_id_texture;
		delete m_ds_render_buffer;
		delete m_frame_buffer;
	}

	void pre_pass::rend(
		render_system* render,
		camera_object* camera,
		vector<mesh_object*>& meshes) {
		m_frame_buffer->bind();
		render->set_clear_color(vec4(0.0f, 0.0f, 0.0f, 0.0f));
		render->set(graphic_capability::DEPTH_TEST, true);
		render->set(graphic_func::DEPTH_MASK, true);
		render->set_depth_func(depth_func::LESS);
		render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);

		m_shader->use();
		m_shader->set_mat4("uProjection", camera->get_projection());
		m_shader->set_mat4("uView", camera->get_view());
		for (vector<mesh_object*>::iterator m_iter = meshes.begin();
			m_iter != meshes.end();
			++m_iter) {
			m_shader->set_mat4("uModel", (*m_iter)->get_world_transform());
			m_shader->set_vec4("uID", get_color((*m_iter)->get_id()));

			for (vector<vertex_buffer*>::iterator vbo_iter = (*m_iter)->m_mesh->m_vbo_buffer.begin();
				vbo_iter != (*m_iter)->m_mesh->m_vbo_buffer.end();
				++vbo_iter) {
				(*vbo_iter)->draw();
			}
		}
	}
}
