#ifndef TIGINE_RHI_GL430_GL430_COMMAND_QUEUE_H_
#define TIGINE_RHI_GL430_GL430_COMMAND_QUEUE_H_

#include "gl430/gl430_common.h"
#include "interface/i_command_queue.h"

namespace tigine { namespace rhi {
class GL430CommandQueue : public ICommandQueue {
public:
    GL430CommandQueue()  = default;
    ~GL430CommandQueue() = default;

    void submit(ICommandBuffer *command_buffer) override {}

private:
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_GL430_GL430_COMMAND_QUEUE_H_
