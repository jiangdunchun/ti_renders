#include "mesh_object.h"

using namespace std;

namespace ti_render {
	mesh_object::mesh_object(const string& mesh_path) {
		m_type = object_type::MESH_OBJECT;

		m_mesh = mesh_factory::create(mesh_path);
		m_materials.resize(m_mesh->get_surface_num(), nullptr);
	}

	mesh_object::~mesh_object() {
		mesh_factory::dispose(m_mesh);
		for (vector<material*>::iterator iter = m_materials.begin();
			iter != m_materials.end();
			++iter) {
			material_factory::dispose((*iter));
		}
	}

	void mesh_object::set_material(const string& material_path, unsigned int surface) {
		material* material_ptr = material_factory::create(material_path);
		set_material(material_ptr, surface);
	}

	void mesh_object::set_material(material* material_ptr, unsigned int surface) {
		if (surface >= m_materials.size()) return;
		m_materials[surface] = material_ptr;
	}
}