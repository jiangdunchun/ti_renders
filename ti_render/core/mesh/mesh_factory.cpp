#include "mesh_factory.h"

#include "../../third_party/md5/md5.h"
#include "../file/mesh_file.h"

using namespace std;

namespace ti_render {
	map<string, tuple<mesh*, unsigned int>> mesh_factory::sm_mesh_pool = {};

	mesh* mesh_factory::create(const string& path) {
		string md5 = MD5(path).toStr();
		map<string, tuple<mesh*, unsigned int>>::iterator iter = sm_mesh_pool.find(md5);
		if (iter == sm_mesh_pool.end()) {
			mesh_file m_file(path);
			mesh* mesh_ptr = new mesh(m_file.get_faces(), m_file.get_aabb());
			sm_mesh_pool[md5] = make_tuple(mesh_ptr, 1);
			return mesh_ptr;
		}
		else {
			get<1>(iter->second)++;
			return get<0>(iter->second);
		}
	}

	void mesh_factory::dispose(mesh* mesh_ptr) {
		for (map<string, tuple<mesh*, unsigned int>>::iterator iter = sm_mesh_pool.begin();
			iter != sm_mesh_pool.end();
			++iter) {
			if (mesh_ptr == get<0>(iter->second)) {
				get<1>(iter->second)--;
				if (get<1>(iter->second) == 0) {
					sm_mesh_pool.erase(iter->first);
					delete mesh_ptr;
					mesh_ptr = nullptr;
				}
				break;
			}
		}
		if (mesh_ptr) {
			delete mesh_ptr;
			mesh_ptr = nullptr;
		}
	}
}