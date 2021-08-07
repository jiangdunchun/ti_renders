#include "pass_management.h"

using namespace std;

namespace ti_render {
	pass_management::pass_management(unsigned int width, unsigned int height) {
		m_pre_pass = new pre_pass(width, height);
		m_geomtry_pass = new geometry_pass(width, height);
		m_sky_pass = new sky_pass(width, height);
	}

	pass_management::~pass_management() {
		delete m_pre_pass;
		delete m_geomtry_pass;
		delete m_sky_pass;
	}

	void pass_management::rend(render_system* render, scene* scene) {
		camera_object* camera = scene->m_camera;
		sky_object* sky = scene->m_sky;
		vector<mesh_object*> meshes = scene->m_mesh_objects;

		m_pre_pass->rend(render, camera, meshes);
		m_geomtry_pass->rend(render, camera, meshes);
		m_sky_pass->rend(render, camera, sky);
	}
}