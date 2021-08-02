#ifndef __MESH_OBJECT_H__
#define __MESH_OBJECT_H__

#include <string>

#include "object.h"
#include "../mesh/mesh_factory.h"
#include "../material/material_factory.h"

namespace ti_render {
	class mesh_object : public object {
		friend class scene;

	private:
		mesh* m_mesh;
		std::vector<material*> m_materials;

		mesh_object(const std::string& mesh_path);
		~mesh_object();

	public:
		void set_material(const std::string& material_path, unsigned int face);
		void set_material(material* material_ptr, unsigned int face);
	};
}

#endif // !__MESH_OBJECT_H__

