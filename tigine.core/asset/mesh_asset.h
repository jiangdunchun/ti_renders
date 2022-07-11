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
		static std::vector<mesh_asset*> load(const std::string path);

		void set_vertices(const std::vector<vertex>& vertices) {
			m_vertices = vertices;
		}
		void set_bones(const std::vector<bone>& bones) {
			m_bones = bones;
		}
		void set_indices(const std::vector<int>& indices) {
			m_indices = indices;
		}
		const std::vector<vertex>& get_vertices() const {
			return m_vertices;
		}
		bool has_bones() const {
			return m_bones.size() != 0;
		}
		const std::vector<bone>& get_bones() const {
			return m_bones;
		}
		bool has_indices() const {
			return m_indices.size() != 0;
		}
		const std::vector<int>& get_indices() const {
			return m_indices;
		}
	};
}

#endif