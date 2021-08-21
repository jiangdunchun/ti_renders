#include "light_pass.h"

#include "../file/shader_file.h"
#include "../file/image_file.h"
#include "../object/point_light_object.h"

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
		vector<point_light_object*> point_lights;
		for (vector<light_object*>::iterator iter = lights.begin();
			iter != lights.end();
			++iter) {
			if ((*iter)->get_type() == object_type::POINT_LIGHT) point_lights.push_back(static_cast<point_light_object*>(*iter));
		}

		m_frame_buffer->bind();
		render->set_clear_color(vec4(0.0f, 0.0f, 0.0f, 0.0f));
		render->set(graphic_capability::TEXTURE_CUBE_MAP_SEAMLESS, true);
		render->set(graphic_capability::DEPTH_TEST, true);
		render->set(graphic_func::DEPTH_MASK, true);
		render->set_depth_func(depth_func::LESS);
		render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);

		m_shader->use();
		m_shader->set_texture_2d("uPosition", *m_position_in);
		m_shader->set_texture_2d("uBase_color", *m_base_color_in);
		m_shader->set_texture_2d("uNormal", *m_normal_in);
		m_shader->set_texture_2d("uMaterial", *m_material_in);
		m_shader->set_vec3("uView", camera->get_world_position());
		m_shader->set_texture_cube("uDiffuse", *(sky->m_diffuse_cube));
		m_shader->set_texture_cube("uSpecular", *(sky->m_specular_cube));
		m_shader->set_texture_2d("uLUT", *m_lut);
		m_shader->set_int("uPoint_lights_num", point_lights.size());
		for (unsigned int i = 0; i < point_lights.size(); i++) {
			string light_name = "uPoint_lights[" + to_string(i) + "]";
			m_shader->set_vec3(light_name + ".position", point_lights[i]->get_world_position());
			m_shader->set_vec3(light_name + ".intensity", point_lights[i]->get_intensity());
			m_shader->set_texture_cube(light_name + ".shadow_map", *(point_lights[i]->m_shadow_map));
			m_shader->set_float(light_name + ".bias", point_lights[i]->get_bias());
			m_shader->set_float(light_name + ".radius", point_lights[i]->get_radius());
		}

		m_mesh->draw();
	}
}