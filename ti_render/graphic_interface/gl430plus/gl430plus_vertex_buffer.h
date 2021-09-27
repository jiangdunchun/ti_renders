#ifndef __GL430PLUS_VERTEX_BUFFER_H__
#define __GL430PLUS_VERTEX_BUFFER_H__

#include "gl430plus_common.h"
#include <vector>

namespace ti_render {
	class gl430plus_vertex_buffer {
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
		unsigned int m_triangle_num;

	public:
		gl430plus_vertex_buffer(const std::vector<vertex>& vertices, const std::vector<unsigned int>& indices);
		~gl430plus_vertex_buffer();
		void draw(void) const;
	};
}

#endif // !__GL430PLUS_VERTEX_BUFFER_H__

