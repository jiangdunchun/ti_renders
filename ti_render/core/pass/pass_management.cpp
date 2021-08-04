#include "pass_management.h"

using namespace std;

namespace ti_render {
	pass_management::pass_management(unsigned int width, unsigned int height) {
		m_pre_pass = new pre_pass(width, height);
	}

	pass_management::~pass_management() {
		delete m_pre_pass;
	}

	void pass_management::rend(render_system* render_system, scene* scene) {
		camera_object* camera = scene->m_camera;
		vector<mesh_object*> meshes = scene->m_mesh_objects;

		m_pre_pass->rend(render_system, camera, meshes);
	}
}