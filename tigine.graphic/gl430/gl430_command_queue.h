#ifndef TIGINE_GRAPHIC_GL430_GL430_COMMAND_QUEUE_H_
#define TIGINE_GRAPHIC_GL430_GL430_COMMAND_QUEUE_H_

#include "gl430/gl430_common.h"
#include "interface/i_command_queue.h"

namespace tigine { namespace graphic {
class GL430CommandQueue : public ICommandQueue {
public:
    GL430CommandQueue()  = default;
    ~GL430CommandQueue() = default;
    DISALLOW_COPY_AND_ASSIGN(GL430CommandQueue);

    void submit(ICommandBuffer *command_buffer) override {}

private:
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_GL430_GL430_COMMAND_QUEUE_H_
