#ifndef TIGINE_GRAPHIC_GL430_GL430_PASS_H_
#define TIGINE_GRAPHIC_GL430_GL430_PASS_H_

#include "gl430/gl430_common.h"

namespace tigine {
namespace graphic {
struct PassDescriptor {
	
};

class GL430Pass {
public:
    GL430Pass(const PassDescriptor& desc);
	~GL430Pass();
    DISALLOW_COPY_AND_ASSIGN(GL430Pass);

private:
};
} // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_GL430_GL430_PASS_H_
