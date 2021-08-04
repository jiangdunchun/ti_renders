#ifndef __MESH_H__
#define __MESH_H__

#include "../../common/tr_struct.h"
#include "../../graphic_interface/graphic_interface.h"

namespace ti_render {
	class mesh {
	friend class mesh_factory;
	friend class pre_pass;

	private:
		std::vector<vertex_buffer*> m_vbo_buffer;
		std::vector<AABB> m_aabb_buffer;
		AABB m_aabb;

		mesh(const std::vector<surface>& faces, const AABB& aabb);
		~mesh();

	public:
		const AABB& get_aabb(void) const {
			return m_aabb;
		}
		unsigned int get_surface_num(void) const;
		const AABB& get_surface_aabb(unsigned int surface) const;
	};
}

#endif // !__MESH_H__

