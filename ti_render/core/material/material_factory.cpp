#include "material_factory.h"

using namespace std;

namespace ti_render {
	map<string, tuple<material*, unsigned int>> material_factory::sm_material_pool = {};

	material* material_factory::create_material(const string& path) {
		return nullptr;
	}

	material* material_factory::create_material(material_type m_type) {
		return nullptr;
	}

	void material_factory::dispose_material(material* material_ptr) {
	}
}