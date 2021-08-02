#include "mesh_object.h"

using namespace std;

namespace ti_render {
	mesh_object::mesh_object(const string& mesh_path) {
		m_mesh = mesh_factory::create(mesh_path);
		m_materials.resize(m_mesh->get_face_num(), nullptr);
	}

	mesh_object::~mesh_object() {
		mesh_factory::dispose(m_mesh);
		for (vector<material*>::iterator iter = m_materials.begin();
			iter != m_materials.end();
			++iter) {
			material_factory::dispose((*iter));
		}
	}

	void mesh_object::set_material(const std::string& material_path, unsigned int face) {
		material* material_ptr = material_factory::create(material_path);
		set_material(material_ptr, face);
	}

	void mesh_object::set_material(material* material_ptr, unsigned int face) {
		if (face >= m_materials.size()) return;
		m_materials[face] = material_ptr;
	}
}