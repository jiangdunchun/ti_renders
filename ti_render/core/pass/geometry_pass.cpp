#include "geometry_pass.h"

using namespace std;
using namespace glm;

namespace ti_render {
	geometry_pass::geometry_pass(unsigned int width, unsigned int height, ds_render_buffer* dbo) {
		m_position = new gl3plus_texture_2d(width, height, color_format::RGB16F);
		m_base_color = new gl3plus_texture_2d(width, height, color_format::RGBA16F);
		m_normal = new gl3plus_texture_2d(width, height, color_format::RGB16F);
		m_material = new gl3plus_texture_2d(width, height, color_format::RGBA16F);
		m_emissive = new gl3plus_texture_2d(width, height, color_format::RGB16F);

		m_frame_buffer = new gl3plus_frame_buffer(width, height, dbo);
		m_frame_buffer->attach_color_buffer(0, m_position);
		m_frame_buffer->attach_color_buffer(1, m_base_color);
		m_frame_buffer->attach_color_buffer(2, m_normal);
		m_frame_buffer->attach_color_buffer(3, m_material);
		m_frame_buffer->attach_color_buffer(4, m_emissive);
	}

	geometry_pass::~geometry_pass() {
		delete m_position;
		delete m_base_color;
		delete m_normal;
		delete m_material;
		delete m_emissive;
		delete m_frame_buffer;
	}

	void geometry_pass::rend(render_system* render, camera_object* camera, vector<mesh_object*> meshes) {
		m_frame_buffer->bind();
		render->set_clear_color(vec4(0.0f, 0.0f, 0.0f, 0.0f));
		render->set(graphic_capability::DEPTH_TEST, true);
		render->set_depth_func(depth_func::LEQUAL);
		render->clear_frame_buffer(frame_buffer_type::COLOR);
		
		for (vector<mesh_object*>::iterator m_iter = meshes.begin();
			m_iter != meshes.end();
			++m_iter) {
			for (int i = 0; i < (*m_iter)->m_mesh->m_vbo_buffer.size(); ++i) {
				material* mat = (*m_iter)->m_materials[i];
				if (mat) {
					mat->m_shader->use();
					mat->m_shader->set_mat4("uProjection", camera->get_projection());
					mat->m_shader->set_mat4("uView", camera->get_view());
					mat->m_shader->set_mat4("uModel", (*m_iter)->get_world_transform());
					mat->m_shader->set_int("uView", (int)mat->get_light_model());
					mat->bind_data();

					(*m_iter)->m_mesh->m_vbo_buffer[i]->draw();
				}
			}
		}

		m_frame_buffer->unbind();
	}
}