#include "material_factory.h"

#include "../../third_party/md5/md5.h"
#include "metallic_roughness_material.h"

using namespace std;

namespace ti_render {
	map<string, tuple<material*, unsigned int>> material_factory::sm_material_pool = {};

	material* material_factory::create(const string& path) {
		string md5 = MD5(path).toStr();
		map<string, tuple<material*, unsigned int>>::iterator iter = sm_material_pool.find(md5);
		if (iter == sm_material_pool.end()) {
			material* material_ptr = nullptr;

			material_file m_file(path);
			material_type m_type = materiral_type_helper::to_type(m_file.get_type());
			switch (m_type) {
			case ti_render::material_type::METALLIC_ROUGHNESS:
				material_ptr = new metallic_roughness_material();
				break;
			default:
				break;
			}
			material_ptr->compile(&m_file);
			sm_material_pool[md5] = make_tuple(material_ptr, 1);
			return material_ptr;
		}
		else {
			get<1>(iter->second)++;
			return get<0>(iter->second);
		}
	}

	material* material_factory::create(material_type m_type) {
		material* material_ptr = nullptr;
		switch (m_type) {
		case ti_render::material_type::METALLIC_ROUGHNESS:
			material_ptr = new metallic_roughness_material();
			break;
		default:
			break;
		}
		material_ptr->compile(nullptr);
		return material_ptr;
	}

	void material_factory::dispose(material* material_ptr) {
		for (map<string, tuple<material*, unsigned int>>::iterator iter = sm_material_pool.begin();
			iter != sm_material_pool.end();
			++iter) {
			if (material_ptr == get<0>(iter->second)) {
				get<1>(iter->second)--;
				if (get<1>(iter->second) == 0) {
					delete material_ptr;
					material_ptr = nullptr;
				}
				sm_material_pool.erase(iter->first);
				break;
			}
		}
		if (material_ptr) {
			delete material_ptr;
			material_ptr = nullptr;
		}
	}
}