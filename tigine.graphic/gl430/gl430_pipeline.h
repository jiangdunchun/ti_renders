#ifndef TIGINE_GRAPHIC_GL430_GL430_PIPELINE_H_
#define TIGINE_GRAPHIC_GL430_GL430_PIPELINE_H_

#include "gl430/gl430_common.h"
#include "gl430/gl430_shader_program.h"

namespace tigine {
namespace graphic {
struct PipelineDescriptor {
	GL430ShaderProgram* shader_program = nullptr;
};

class GL430Pipeline {
public:
	GL430Pipeline(const PipelineDescriptor& desc);
	~GL430Pipeline();
    DISALLOW_COPY_AND_ASSIGN(GL430Pipeline);

private:
};
} // namespace tigine::graphic
} // namespace tigine

#endif // !TIGINE_GRAPHIC_GL430_GL430_PIPELINE_H_
