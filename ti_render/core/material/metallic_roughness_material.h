#ifndef __METALLIC_ROUGHNESS_H__
#define __METALLIC_ROUGHNESS_H__

#include "material.h"

namespace ti_render {
	class metallic_roughness_material : public material {
	friend class material_factory;

	private:
		metallic_roughness_material() {
			m_type = material_type::METALLIC_ROUGHNESS;
			m_light_model = light_model::PBR;
			m_shader_path = "shader/metallic_roughness_material.shader";
			m_parameters = {
				{"uBase_color_val", value_type::VEC3, "0.5f, 0.5f, 0.5f"},
				{"uBase_color_map", value_type::TEXTURE2D},
				{"uNormal_map", value_type::TEXTURE2D},
				{"uMetallic_val", value_type::FLOAT, "0.0f"},
				{"uMetallic_map", value_type::TEXTURE2D},
				{"uRoughness_val", value_type::FLOAT, "0.0f"},
				{"uRoughness_map", value_type::TEXTURE2D},
				{"uHeight_map", value_type::TEXTURE2D},
				{"uHeight_val", value_type::FLOAT, "0.0f"},
				{"uAo_map", value_type::TEXTURE2D},
				{"uEmissive_map", value_type::TEXTURE2D}
			};
		}
	};
}

#endif // !__METALLIC_ROUGHNESS_H__
