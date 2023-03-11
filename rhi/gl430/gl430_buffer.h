#ifndef TIGINE_RHI_GL430_GL430_BUFFER_H_
#define TIGINE_RHI_GL430_GL430_BUFFER_H_

#include "gl430/gl430_common.h"
#include "interface/i_buffer.h"

namespace tigine { namespace rhi {
class GL430Buffer : public IBuffer {
public:
    GL430Buffer(const BufferDesc &desc, const void *data);
    ~GL430Buffer();

    GLuint getID() const { return id_; }

private:
    GLuint id_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_GL430_GL430_BUFFER_H_
