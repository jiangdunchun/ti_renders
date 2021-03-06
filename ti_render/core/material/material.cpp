#include "material.h"

#include "../../common/tr_string_parser.h"
#include "../../third_party/md5/md5.h"
#include "../file/image_file.h"
#include "../file/shader_file.h"

using namespace std;
using namespace glm;

namespace ti_render {
	texture_2d* material::sm_nill_texture_2d = nullptr;
	map<string, tuple<texture_2d*, unsigned int>> material::sm_texture_2d_pool = {};
	map<string, tuple<shader*, unsigned int>> material::sm_shader_pool = {};

	texture_2d* material::create_texture_2d(const string& path) {
		string md5 = MD5(path).toStr();
		map<string, tuple<texture_2d*, unsigned int>>::iterator iter = sm_texture_2d_pool.find(md5);
		if (iter == sm_texture_2d_pool.end()) {
			image_file i_file(path, color_format::RGB8B);
			if (i_file.get_width() == 0 || i_file.get_height() == 0) {
				if (!sm_nill_texture_2d) sm_nill_texture_2d = new texture_2d(0, 0, color_format::RGB8B);

				return sm_nill_texture_2d;
			}

			texture_2d* texture_2d_ptr = new texture_2d(i_file.get_width(), i_file.get_height(), color_format::RGB8B);
			texture_2d_ptr->push_data(i_file.get_color_format(), i_file.get_data());
			sm_texture_2d_pool[md5] = make_tuple(texture_2d_ptr, 1);
			return texture_2d_ptr;
		}
		else {
			get<1>(iter->second)++;
			return get<0>(iter->second);
		}
	}

	void material::dispose_texture_2d(texture_2d* texture_ptr) {
		if (texture_ptr == sm_nill_texture_2d) {
			texture_ptr = nullptr;
			return;
		}

		for (map<string, tuple<texture_2d*, unsigned int>>::iterator iter = sm_texture_2d_pool.begin();
			iter != sm_texture_2d_pool.end();
			++iter) {
			if (texture_ptr == get<0>(iter->second)) {
				get<1>(iter->second)--;
				if (get<1>(iter->second) == 0) {
					sm_texture_2d_pool.erase(iter->first);
					delete texture_ptr;
				}
				break;
			}
		}
		texture_ptr = nullptr;
	}

	shader* material::create_shader(const string& path) {
		string md5 = MD5(path).toStr();
		map<string, tuple<shader*, unsigned int>>::iterator iter = sm_shader_pool.find(md5);
		if (iter == sm_shader_pool.end()) {
			shader_file s_file(path);
			if (s_file.get_vertex_code() == "" || s_file.get_fragment_code() == "") throw "error shader file!";

			shader* shader_ptr = new shader(s_file.get_vertex_code(), s_file.get_fragment_code(), s_file.get_geometry_code());
			sm_shader_pool[md5] = make_tuple(shader_ptr, 1);
			return shader_ptr;
		}
		else {
			get<1>(iter->second)++;
			return get<0>(iter->second);
		}
	}

	void material::dispose_shader(shader* shader_ptr) {
		for (map<string, tuple<shader*, unsigned int>>::iterator iter = sm_shader_pool.begin();
			iter != sm_shader_pool.end();
			++iter) {
			if (shader_ptr == get<0>(iter->second)) {
				get<1>(iter->second)--;
				if (get<1>(iter->second) == 0) {
					sm_shader_pool.erase(iter->first);
					delete shader_ptr;
				}
				break;
			}
		}
		shader_ptr = nullptr;
	}

	void material::delete_val_ptr(void*& ptr, value_type p_type) {
		if (!ptr) return;

		switch (p_type) {
		case value_type::NILL:
			break;
		case value_type::INT:
			delete (int*)ptr;
			break;
		case value_type::FLOAT:
			delete (float*)ptr;
			break;
		case value_type::VEC2:
			delete (vec2*)ptr;
			break;
		case value_type::VEC3:
			delete (vec3*)ptr;
			break;
		case value_type::VEC4:
			delete (vec4*)ptr;
			break;
		case value_type::MAT2:
			delete (mat2*)ptr;
			break;
		case value_type::MAT3:
			delete (mat3*)ptr;
			break;
		case value_type::MAT4:
			delete (mat4*)ptr;
			break;
		case value_type::TEXTURE2D:
			dispose_texture_2d((texture_2d*)ptr);
			break;
		}
		ptr = nullptr;
	}

	void material::create_val_ptr(void*& ptr, value_type p_type, string val_str) {
		delete_val_ptr(ptr, p_type);

		switch (p_type) {
		case value_type::NILL:
			break;
		case value_type::INT:
			ptr = new int();
			*(int*)ptr = atoi(val_str.c_str());
			break;
		case value_type::FLOAT:
			ptr = new float();
			*(float*)ptr = atof(val_str.c_str());
			break;
		case value_type::VEC2:
			ptr = new vec2();
			*(vec2*)ptr = tr_string_parser::to_vec2(val_str);
			break;
		case value_type::VEC3:
			ptr = new vec3();
			*(vec3*)ptr = tr_string_parser::to_vec3(val_str);
			break;
		case value_type::VEC4:
			ptr = new vec4();
			*(vec4*)ptr = tr_string_parser::to_vec4(val_str);
			break;
		case value_type::MAT2:
			ptr = new mat2();
			*(mat2*)ptr = tr_string_parser::to_mat2(val_str);
			break;
		case value_type::MAT3:
			ptr = new mat3();
			*(mat3*)ptr = tr_string_parser::to_mat3(val_str);
			break;
		case value_type::MAT4:
			ptr = new mat4();
			*(mat4*)ptr = tr_string_parser::to_mat4(val_str);
			break;
		case value_type::TEXTURE2D:
			ptr = create_texture_2d(val_str);
			break;
		}
	}

	void material::bind_data(void) {
		for (map<string, tuple<value_type, void*>>::iterator iter = m_parameter_buffer.begin();
			iter != m_parameter_buffer.end();
			++iter){
			string p_name = iter->first;
			value_type p_type = get<0>(iter->second);
			void* p_value = get<1>(iter->second);

			switch (p_type) {
			case value_type::NILL:
				break;
			case value_type::INT:
				m_shader->set_int(p_name, *(int*)p_value);
				break;
			case value_type::FLOAT:
				m_shader->set_float(p_name, *(float*)p_value);
				break;
			case value_type::VEC2:
				m_shader->set_vec2(p_name, *(vec2*)p_value);
				break;
			case value_type::VEC3:
				m_shader->set_vec3(p_name, *(vec3*)p_value);
				break;
			case value_type::VEC4:
				m_shader->set_vec4(p_name, *(vec4*)p_value);
				break;
			case value_type::MAT2:
				m_shader->set_mat2(p_name, *(mat2*)p_value);
				break;
			case value_type::MAT3:
				m_shader->set_mat3(p_name, *(mat3*)p_value);
				break;
			case value_type::MAT4:
				m_shader->set_mat4(p_name, *(mat4*)p_value);
				break;
			case value_type::TEXTURE2D:
				m_shader->set_texture_2d(p_name, *(gl430plus_texture_2d*)p_value);
				break;
			}
		}
	}

	void material::compile(material_file* m_file) {
		// read material parameters
		for (vector<material_parameter>::iterator iter = m_parameters.begin();
			iter != m_parameters.end();
			++iter) {
			map<string, tuple<value_type, void*>>::iterator p_iter;
			p_iter = m_parameter_buffer.find(iter->name);
			if (p_iter == m_parameter_buffer.end()) {
				void* value_ptr = nullptr;
				if (m_file) {
					string value_str = m_file->get_value(iter->name);
					create_val_ptr(value_ptr, iter->type, value_str);
				}
				else {
					create_val_ptr(value_ptr, iter->type, iter->default_value);
				}

				m_parameter_buffer[iter->name] = make_tuple(iter->type, value_ptr);
			}
		}

		// load shader
		m_shader = create_shader(m_shader_path);
	}

	material::~material() {
		if (m_shader != nullptr) dispose_shader(m_shader);

		for (map<string, tuple<value_type, void*>>::iterator iter = m_parameter_buffer.begin();
			iter != m_parameter_buffer.end();
			++iter) {
			value_type p_type = get<0>(iter->second);
			void* p_value = get<1>(iter->second);
			delete_val_ptr(p_value, p_type);
		}
	}

	void material::set_value(const material_parameter& parameter, const string& value) {
		map<string, tuple<value_type, void*>>::iterator p_iter = m_parameter_buffer.find(parameter.name);
		if (p_iter != m_parameter_buffer.end() && get<0>(p_iter->second) == parameter.type) {
			create_val_ptr(get<1>(p_iter->second), get<0>(p_iter->second), value);
		}
	}
}