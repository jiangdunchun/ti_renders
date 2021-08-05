#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <map>
#include <vector>

#include "../../graphic_interface/graphic_interface.h"
#include "../file/material_file.h"
#include "material_common.h"

namespace ti_render {
	class material {
	friend class material_factory;
	friend class geometry_pass;

	private:
		static texture_2d* sm_nill_texture_2d;
		static std::map<std::string, std::tuple<texture_2d*, unsigned int>> sm_texture_2d_pool;
		static std::map<std::string, std::tuple<shader*, unsigned int>> sm_shader_pool;

		shader* m_shader;
		std::map<std::string, std::tuple<value_type, void*>> m_parameter_buffer;

		texture_2d* create_texture_2d(const std::string& path);
		void dispose_texture_2d(texture_2d* texture_ptr);
		shader* create_shader(const std::string& path);
		void dispose_shader(shader* shader_ptr);
		void delete_val_ptr(void*& ptr, value_type p_type);
		void create_val_ptr(void*& ptr, value_type p_type, void* val_ptr);
		void create_val_ptr(void*& ptr, value_type p_type, std::string val_str);

	protected:
		material_type m_type;
		light_model m_light_model;
		std::string m_shader_path;
		std::vector<material_parameter> m_parameters;

		void compile(material_file* m_file);

		virtual ~material();

	public:
		const material_type& get_type(void) const {
			return m_type;
		}
		const light_model& get_light_model(void) const {
			return m_light_model;
		}
		void bind(void);
		void set_value_temporary(const material_parameter& parameter, void* value);
		void set_value_permanent(const material_parameter& parameter, void* value);
	};
}

#endif // !__MATERIAL_H__