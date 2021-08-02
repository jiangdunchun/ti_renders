#ifndef __MESH_FILE_H__
#define __MESH_FILE_H__

#include <vector>
#include <string>
#include <map>

#include "../../common/tr_struct.h"

namespace ti_render {
	class mesh_file {
	private:
		std::vector<face> m_faces;
		AABB m_aabb;

	public:
		mesh_file(const std::string& path);
		mesh_file(std::vector<face> faces, AABB aabb);
		~mesh_file();

		void save(const std::string& path);
		const std::vector<face>& get_faces(void) const {
			return m_faces;
		}
		const AABB& get_aabb(void) const {
			return m_aabb;
		}
	};
}

#endif // !__MESH_FILE_H__

