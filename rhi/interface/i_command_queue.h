#ifndef TIGINE_RHI_INTERFACE_I_COMMAND_QUEUE_H_
#define TIGINE_RHI_INTERFACE_I_COMMAND_QUEUE_H_

#include "interface/i_command_buffer.h"
#include "interface/i_common.h"

namespace tigine { namespace rhi {
class ICommandQueue : public NonCopyable {
public:
    virtual void submit(ICommandBuffer *command_buffer) = 0;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_COMMAND_QUEUE_H_
