#ifndef __MESH_FACTORY_H__
#define __MESH_FACTORY_H__

#include <map>
#include <string>

#include "mesh.h"

namespace ti_render {
	class mesh_factory {
	private:
		static std::map<std::string, std::tuple<mesh*, unsigned int>> sm_mesh_pool;
	public:
		static mesh* create(const std::string& path);
		static void dispose(mesh* mesh_ptr);
	};
}

#endif // !__MESH_FACTORY_H__
