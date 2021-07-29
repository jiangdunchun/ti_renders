#include "material_common.h"

using namespace std;

namespace ti_render {
	string materiral_type_helper::enum_str[] = {
		"METALLIC_ROUGHNESS"
	};

	string materiral_type_helper::to_string(material_type type) {
		if (type == material_type::NILL) return "";

		return materiral_type_helper::enum_str[(int)type];
	}

	material_type materiral_type_helper::to_type(string type_str) {
		int enum_count = sizeof(materiral_type_helper::enum_str) / sizeof(materiral_type_helper::enum_str[0]);
		for (int i = 0; i < enum_count; i++) {
			if (materiral_type_helper::enum_str[i] == type_str) return (material_type)i;
		}
		return material_type::NILL;
	}
}