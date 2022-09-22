#ifndef TIGINE_GRAPHIC_GL430_GL430_BUFFER_ARRAY_H_
#define TIGINE_GRAPHIC_GL430_GL430_BUFFER_ARRAY_H_

#include <vector>

#include "gl430/gl430_common.h"
#include "interface/i_buffer_array.h"

namespace tigine { namespace graphic {
class GL430BufferArray : public IBufferArray {
public:
    explicit GL430BufferArray(const BufferArrayDescriptor &desc);
    ~GL430BufferArray();
    DISALLOW_COPY_AND_ASSIGN(GL430BufferArray);

    GLuint getID() const { return id_; }

private:
    GLuint id_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_GL430_GL430_BUFFER_ARRAY_H_
