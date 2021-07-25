#ifndef __MESH_FILE_H__
#define __MESH_FILE_H__

#include <vector>
#include <string>
#include <map>

#include "../../common/tr_struct.h"

namespace ti_render {
	class mesh_file {
	private:
		std::vector<vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		AABB m_AABB;

	public:
		mesh_file(const std::string& path);
		mesh_file(
			const std::vector<vertex>& vertices,
			const std::vector<unsigned int>& indices,
			glm::vec3 AABB_min = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 AABB_max = glm::vec3(0.0f, 0.0f, 0.0f));
		~mesh_file();

		void save(const std::string& path) const;
		const std::vector<vertex>& get_vertices(void) const {
			return this->m_vertices;
		}
		const std::vector<unsigned int>& get_indices(void) const {
			return this->m_indices;
		}
		const AABB& get_AABB(void) const {
			return this->m_AABB;
		}
	};
}

#endif // !__MESH_FILE_H__

