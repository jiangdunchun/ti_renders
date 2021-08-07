#include "shadow_map_pass.h"

using namespace std;
using namespace glm;

namespace ti_render {
	shadow_map_pass::shadow_map_pass() {
		shader_file s_file(m_shader_path);
		m_shader = new shader(s_file.get_vertex_code(), s_file.get_fragment_code());
	}

	shadow_map_pass::~shadow_map_pass() {
		delete this->m_shader;
	}

	void shadow_map_pass::rend(render_system* render, vector<light_object*> lights, vector<mesh_object*> meshes) {
	}
}