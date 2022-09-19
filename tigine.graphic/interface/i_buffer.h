#ifndef TIGINE_GRAPHIC_INTERFACE_I_BUFFER_H_
#define TIGINE_GRAPHIC_INTERFACE_I_BUFFER_H_

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

class IBuffer {
public:
	IBuffer(const BufferDescriptor& desc);
	virtual ~IBuffer() = 0;

private:
	
};
} // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_INTERFACE_I_BUFFER_H_
