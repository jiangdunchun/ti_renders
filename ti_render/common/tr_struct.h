#ifndef __TR_STRUCT_H__
#define __TR_STRUCT_H__

#include <glm/glm.hpp>

namespace ti_render {
	struct vertex {
		glm::vec3 position;
		glm::vec2 tex_coord;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 bi_tangent;
	};

	struct AABB {
		glm::vec3 min;
		glm::vec3 max;
	};
}

#endif // !__TR_STRUCT_H__

