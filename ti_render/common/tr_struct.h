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

	struct point;
	struct edge;
	struct triangle {
		point* p0;
		point* p1;
		point* p2;
		edge* e0;
		edge* e1;
		edge* e2;
	};

	struct edge {
		std::vector<triangle*> ts;
		point* p0;
		point* p1;
	};

	struct point {
		std::vector<triangle*> ts;
		std::vector<edge*> es;
		vertex* v;
	};
}

#endif // !__TR_STRUCT_H__

