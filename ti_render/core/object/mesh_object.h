#ifndef __MESH_OBJECT_H__
#define __MESH_OBJECT_H__

#include <string>

#include "object.h"
#include "../mesh/mesh_factory.h"
#include "../material/material_factory.h"

namespace ti_render {
	class mesh_object : public object {
		friend class scene;
		friend class pre_pass;
		friend class geometry_pass;
		friend class shadowmap_pass;

	private:
		mesh* m_mesh;
		std::vector<material*> m_materials;

		mesh_object(const std::string& mesh_path);
		~mesh_object();

	public:
		void set_material(const std::string& material_path, unsigned int surface);
		void set_material(material* material_ptr, unsigned int surface);
	};
}

#endif // !__MESH_OBJECT_H__

