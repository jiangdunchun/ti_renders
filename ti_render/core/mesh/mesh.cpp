#include "mesh.h"

using namespace std;

namespace ti_render {
	mesh::mesh(const vector<surface>& faces, const AABB& aabb) : m_aabb(aabb) {
		for (vector<surface>::const_iterator iter = faces.begin();
			iter != faces.end();
			++iter) {
			m_aabb_buffer.push_back(iter->aabb);

			vertex_buffer* vbo = new vertex_buffer(iter->vertices, iter->indices);
			m_vbo_buffer.push_back(vbo);
		}
	}

	mesh::~mesh() {
		for (vector<vertex_buffer*>::iterator iter = m_vbo_buffer.begin();
			iter != m_vbo_buffer.end();
			++iter) {
			delete (*iter);
		}
	}

	unsigned int mesh::get_surface_num(void) const {
		return m_vbo_buffer.size();
	}

	const AABB& mesh::get_surface_aabb(unsigned int surface) const{
		return m_aabb_buffer[surface];
	}
}


