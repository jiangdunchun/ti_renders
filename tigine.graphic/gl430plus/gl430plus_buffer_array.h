#ifndef __GL430PLUS_BUFFER_ARRAY_H__
#define __GL430PLUS_BUFFER_ARRAY_H__

#include "gl430plus_buffer.h"

namespace tigine {
    struct vertex_attribute {
        std::string name;
        data_format format;
        std::uint32_t location;
        std::uint32_t offset;
        std::uint32_t stride;
    };

	struct buffer_array_descriptor {
        gl430plus_buffer* vertices_buffer;
        gl430plus_buffer* indices_buffer = nullptr;
        std::vector<vertex_attribute> vertex_attributes;
	};

	class gl430plus_buffer_array {
	private:
		GLuint m_id;

	public:
        gl430plus_buffer_array(const buffer_array_descriptor& desc);
        ~gl430plus_buffer_array();
        GLuint get_id() const {
            return m_id;
        }
	};
}

#endif // !__GL430PLUS_BUFFER_ARRAY_H__