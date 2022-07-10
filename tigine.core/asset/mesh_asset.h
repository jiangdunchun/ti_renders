#ifndef __MESH_ASSET_H__
#define __MESH_ASSET_H__

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace tigine {
	struct vertex {
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec4 jointIndices;
		glm::vec4 jointWeights;
	};

	struct bone {
		int index;
		glm::mat4 offset;
	};

	class mesh_asset {
	private:
		std::vector<vertex> m_vertices;
		std::vector<bone> m_bones;
		std::vector<int> m_indices;

	public:
		static mesh_asset* load(const std::string path);
	};
}

#endif