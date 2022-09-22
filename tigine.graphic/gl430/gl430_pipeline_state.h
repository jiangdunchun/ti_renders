#ifndef TIGINE_GRAPHIC_GL430_GL430_PIPELINE_STATE_H_
#define TIGINE_GRAPHIC_GL430_GL430_PIPELINE_STATE_H_

#include "gl430/gl430_common.h"
#include "interface/i_pipeline_state.h"

namespace tigine { namespace graphic {
class GL430PipelineState : public IPipelineState {
public:
    GL430PipelineState(const PipelineStateDescriptor &desc) : IPipelineState(desc) {}
    ~GL430PipelineState() = default;
    DISALLOW_COPY_AND_ASSIGN(GL430PipelineState);

private:
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_GL430_GL430_PIPELINE_STATE_H_
