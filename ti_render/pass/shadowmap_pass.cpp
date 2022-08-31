#include "shadowmap_pass.h"

#include "../file/shader_file.h"
#include "../object/point_light_object.h"

using namespace std;
using namespace glm;

namespace ti_render {
	shadowmap_pass::shadowmap_pass() {
		shader_file s_file(m_point_light_shader_path);
		m_point_light_shader = new shader(s_file.get_vertex_code(), s_file.get_fragment_code());
	}

	shadowmap_pass::~shadowmap_pass() {
		delete this->m_point_light_shader;
	}

	void shadowmap_pass::rend(render_system* render, vector<light_object*>& lights, vector<mesh_object*>& meshes) {
		for (vector<light_object*>::iterator l_iter = lights.begin();
			l_iter != lights.end();
			++l_iter) {
			if ((*l_iter)->get_type() == object_type::POINT_LIGHT) {
				point_light_object* p_obj = static_cast<point_light_object*>(*l_iter);

				mat4 projection = perspective(90.0f, 1.0f, p_obj->get_bias(), p_obj->get_radius());
				vec3 view_position = p_obj->get_world_position();
				vector<mat4> cube_views = {
					lookAt(view_position, view_position + vec3(1.0f,  0.0f,  0.0f), vec3(0.0f, -1.0f,  0.0f)),
					lookAt(view_position, view_position + vec3(-1.0f,  0.0f,  0.0f), vec3(0.0f, -1.0f,  0.0f)),
					lookAt(view_position, view_position + vec3(0.0f,  1.0f,  0.0f), vec3(0.0f,  0.0f,  1.0f)),
					lookAt(view_position, view_position + vec3(0.0f, -1.0f,  0.0f), vec3(0.0f,  0.0f, -1.0f)),
					lookAt(view_position, view_position + vec3(0.0f,  0.0f,  1.0f), vec3(0.0f, -1.0f,  0.0f)),
					lookAt(view_position, view_position + vec3(0.0f,  0.0f, -1.0f), vec3(0.0f, -1.0f,  0.0f))
				};

				p_obj->m_frame_buffer->bind();
				render->set_clear_color(vec4(p_obj->get_radius()));
				render->set(graphic_capability::DEPTH_TEST, true);
				render->set(graphic_func::DEPTH_MASK, true);
				render->set_depth_func(depth_func::LESS);

				m_point_light_shader->use();
				m_point_light_shader->set_mat4("uProjection", projection);
				m_point_light_shader->set_vec3("uLight_position", view_position);
				m_point_light_shader->set_float("uLight_radius", p_obj->get_radius());
				for (unsigned int i = 0; i < cube_views.size(); ++i) {
					m_point_light_shader->set_mat4("uView", cube_views[i]);
					p_obj->m_frame_buffer->attach_color_buffer(0, p_obj->m_shadow_map, cubemap_face(int(cubemap_face::POSITIVE_X) + i));
					render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);

					for (vector<mesh_object*>::iterator m_iter = meshes.begin();
						m_iter != meshes.end();
						++m_iter) {
						m_point_light_shader->set_mat4("uModel", (*m_iter)->get_world_transform());

						for (vector<vertex_buffer*>::iterator vbo_iter = (*m_iter)->m_mesh->m_vbo_buffer.begin();
							vbo_iter != (*m_iter)->m_mesh->m_vbo_buffer.end();
							++vbo_iter) {
							(*vbo_iter)->draw();
						}
					}
				}
			}
		}
	}
}