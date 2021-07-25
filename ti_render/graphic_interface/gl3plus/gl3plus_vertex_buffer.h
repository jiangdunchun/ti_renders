#ifndef __GL3PLUS_VERTEX_BUFFER_H__
#define __GL3PLUS_VERTEX_BUFFER_H__

#include "gl3plus_common.h"
#include <vector>

namespace ti_render {
	class gl3plus_vertex_buffer {
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
		unsigned int m_triangle_num;

	public:
		gl3plus_vertex_buffer(const std::vector<vertex>& vertices, const std::vector<unsigned int>& indices);
		~gl3plus_vertex_buffer();
		void draw(void) const;
	};
}

#endif // !__GL3PLUS_VERTEX_BUFFER_H__

