#ifndef TIGINE_GRAPHIC_INTERFACE_I_COMMAND_QUEUE_H_
#define TIGINE_GRAPHIC_INTERFACE_I_COMMAND_QUEUE_H_

#include "interface/i_command_buffer.h"
#include "interface/i_common.h"

namespace tigine { namespace graphic {
class ICommandQueue {
public:
    virtual void submit(ICommandBuffer *command_buffer) = 0;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_COMMAND_QUEUE_H_
