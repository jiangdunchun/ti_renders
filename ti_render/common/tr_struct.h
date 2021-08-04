#ifndef __TR_STRUCT_H__
#define __TR_STRUCT_H__

#include <glm/glm.hpp>
#include <vector>

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

	struct surface {
		std::vector<vertex> vertices;
		std::vector<unsigned int> indices;
		AABB aabb;
	};

	struct ray {
		glm::vec3 origin;
		glm::vec3 direction;
	};

	struct triangle {
		vertex* p0;
		vertex* p1;
		vertex* p2;
	};
}

#endif // !__TR_STRUCT_H__

