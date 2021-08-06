#ifndef __MATERIAL_COMMON_H__
#define __MATERIAL_COMMON_H__

#include <string>

namespace ti_render {
	enum class material_type {
		NILL = -1,
		METALLIC_ROUGHNESS = 0,
	};

	class materiral_type_helper {
	private:
		static std::string enum_str[];

	public:
		static std::string to_string(material_type type);
		static material_type to_type(std::string type_str);
	};

	enum class value_type {
		NILL = -1,
		INT = 0,
		FLOAT,
		VEC2,
		VEC3,
		VEC4,
		MAT2,
		MAT3,
		MAT4,
		TEXTURE2D
	};

	enum class light_model {
		SINGLE_COLOR = 1,
		PBR,
	};

	struct material_parameter {
		std::string name;
		value_type type;
		std::string default_value;
	};
}

#endif // !__MATERIAL_COMMON_H__

