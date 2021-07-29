#ifndef __MESH_H__
#define __MESH_H__

#include "../../common/tr_struct.h"
#include "../../graphic_interface/graphic_interface.h"

namespace ti_render {
	class mesh {
	friend class mesh_factory;

	private:
		std::vector<vertex_buffer*> m_vbo_buffer;
		std::vector<AABB> m_aabb_buffer;
		AABB m_aabb;

		mesh(const std::vector<face>& faces, const AABB& aabb);
		~mesh();

	public:
		const AABB& get_aabb(void) const {
			return m_aabb;
		}
		unsigned int get_face_num(void) const;
		const AABB& get_face_aabb(unsigned int face) const;
	};
}

#endif // !__MESH_H__

