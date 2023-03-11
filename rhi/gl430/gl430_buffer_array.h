#ifndef TIGINE_RHI_GL430_GL430_BUFFER_ARRAY_H_
#define TIGINE_RHI_GL430_GL430_BUFFER_ARRAY_H_

#include <vector>

#include "gl430/gl430_common.h"
#include "interface/i_buffer_array.h"

namespace tigine { namespace rhi {
class GL430BufferArray : public IBufferArray {
public:
    explicit GL430BufferArray(const BufferArrayDesc &desc);
    ~GL430BufferArray();

    GLuint getID() const { return id_; }

private:
    GLuint id_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_GL430_GL430_BUFFER_ARRAY_H_
