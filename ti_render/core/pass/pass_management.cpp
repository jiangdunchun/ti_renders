#include "pass_management.h"

using namespace std;

namespace ti_render {
	pass_management::pass_management(unsigned int width, unsigned int height) {
		m_pre_pass = new pre_pass(width, height);
		m_geomtry_pass = new geometry_pass(width, height);
		m_sky_pass = new sky_pass(width, height);
		m_shadowmap_pass = new shadowmap_pass();
		m_emissive_pass = new emissive_pass(width, height, m_geomtry_pass->get_emissive());
	}

	pass_management::~pass_management() {
		delete m_pre_pass;
		delete m_geomtry_pass;
		delete m_sky_pass;
		delete m_shadowmap_pass;
		delete m_emissive_pass;
	}

	void pass_management::rend(render_system* render, scene* scene) {
		camera_object* camera = scene->m_camera;
		sky_object* sky = scene->m_sky;
		vector<mesh_object*> meshes = scene->m_mesh_objects;
		vector<light_object*> lights = scene->m_light_objects;

		m_pre_pass->rend(render, camera, meshes);
		m_geomtry_pass->rend(render, camera, meshes);
		m_sky_pass->rend(render, camera, sky);
		m_shadowmap_pass->rend(render, lights, meshes);
		m_emissive_pass->rend(render);
	}
}