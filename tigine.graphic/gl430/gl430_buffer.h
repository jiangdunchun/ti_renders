#ifndef TIGINE_GRAPHIC_GL430_GL430_BUFFER_H_
#define TIGINE_GRAPHIC_GL430_GL430_BUFFER_H_

#include <cstdint>

#include "gl430/gl430_common.h"
#include "interface/i_buffer.h"

namespace tigine { namespace graphic {
class GL430RenderSystem;
class GL430Buffer : public IBuffer {
public:
    DISALLOW_COPY_AND_ASSIGN(GL430Buffer);

    GLuint getID() const { return id_; }

private:
    friend class GL430RenderSystem;
    GL430Buffer(const BufferDescriptor& desc, const void* data);
    ~GL430Buffer();

    GLuint id_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_GL430_GL430_BUFFER_H_
