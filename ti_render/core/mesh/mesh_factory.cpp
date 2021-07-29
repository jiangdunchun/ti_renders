#include "mesh_factory.h"

using namespace std;

namespace ti_render {
	map<string, tuple<mesh*, unsigned int>> mesh_factory::sm_mesh_pool = {};

	mesh* mesh_factory::create_mesh(const string& path) {
		return nullptr;
	}

	mesh* mesh_factory::create_mesh(const vector<face>& faces, const AABB& aabb) {
		return nullptr;
	}

	void mesh_factory::dispose_mesh(mesh* mesh_ptr) {
	}
}