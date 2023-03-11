#ifndef TIGINE_RHI_INTERFACE_I_SURFACE_H_
#define TIGINE_RHI_INTERFACE_I_SURFACE_H_

#include <string>

#include "interface/i_common.h"

namespace tigine { namespace rhi {
class ISurface : public NonCopyable {
public:
    virtual void setTitle(const std::string &name) = 0;
    virtual void show()                            = 0;
    virtual bool processEvents()                   = 0;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_SURFACE_H_
