#ifndef TIGINE_GRAPHIC_GL430_GL430_BUFFER_H_
#define TIGINE_GRAPHIC_GL430_GL430_BUFFER_H_

#include <cstdint>

#include "gl430/gl430_common.h"

namespace tigine {
namespace graphic {
enum BufferKind {
	BK_Array = (1 << 0),
	BK_ElementArray = (1 << 1),
};

struct BufferDescriptor {
	std::uint64_t size = 0;
	std::uint32_t kinds = 0;
};

class GL430Buffer {
public:
	GL430Buffer(const BufferDescriptor& desc, const void* data);
	~GL430Buffer();
	DISALLOW_COPY_AND_ASSIGN(GL430Buffer);

	GLuint getID() const {
		return id_;
	}

private:
	GLuint id_;
};
} // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_GL430_GL430_BUFFER_H_
