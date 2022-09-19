#ifndef TIGINE_GRAPHIC_GL430_GL430_COMMAND_QUEUE_H_
#define TIGINE_GRAPHIC_GL430_GL430_COMMAND_QUEUE_H_

#include "gl430/gl430_common.h"
#include "gl430/gl430_command_buffer.h"

namespace tigine {
namespace graphic {
class GL430CommandQueue {
public:
    GL430CommandQueue() = default;
    ~GL430CommandQueue() = default;
    DISALLOW_COPY_AND_ASSIGN(GL430CommandQueue);

    void submit(GL430CommandBuffer* command_buffer) {}

private:
};
} // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_GL430_GL430_COMMAND_QUEUE_H_
