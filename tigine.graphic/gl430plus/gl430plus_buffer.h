#ifndef __GL430PLUS_BUFFER_H__
#define __GL430PLUS_BUFFER_H__

#include <cstdint>
#include <string>
#include <vector>
#include "gl430plus_common.h"

namespace tigine {
    enum buffer_descriptor_flags{
        ARRAY_BUFFER = (1 << 0),
		ELEMENT_ARRAY_BUFFER = (1 << 0),
    };

	struct buffer_descriptor {
		std::uint64_t size = 0;
        std::uint32_t flags = 0;
	};

	class gl430plus_buffer {
	private:
		GLuint m_id;
		std::uint32_t m_flags;

	public:
        gl430plus_buffer(const buffer_descriptor& desc, const void* data);
        ~gl430plus_buffer();
		std::uint32_t get_flags() const {
			return m_flags;
		}
		GLuint get_id() const {
			return m_id;
		}
	};
}

#endif // !__GL430PLUS_BUFFER_H__
