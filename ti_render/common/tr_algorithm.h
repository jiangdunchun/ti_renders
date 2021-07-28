#ifndef __TR_ALGORITHM_H__
#define __TR_ALGORITHM_H__

#include "tr_struct.h"

namespace ti_render {
	class tr_algorithm {
	public:
		static void decompose_mat4(const glm::mat4& tansform, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale);
		static bool is_contain_in_AABB(glm::vec3 point, AABB aabb_o, glm::mat4 aabb_o_trans = glm::mat4(1.0f));
		static bool is_intersect_with_AABB(ray ray, AABB aabb, glm::mat4 aabb_trans = glm::mat4(1.0f));
	};
	
}

#endif // !__TR_ALGORITHM_H__

