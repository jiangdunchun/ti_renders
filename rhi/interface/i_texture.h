#ifndef TIGINE_RHI_INTERFACE_I_TEXTURE_H_
#define TIGINE_RHI_INTERFACE_I_TEXTURE_H_

#include "interface/i_common.h"
#include "interface/i_resource.h"

namespace tigine { namespace rhi {
enum class TextureKind {
    Texture1D,
    Texture2D,
    Texture3D,
    TextureCube
};

enum class SamplerAddressMode {
    Repeat,
    Mirror,
    Clamp,
    Border,
    MirrorOnce,
};

enum class SamplerFilter {
    Nearest,
    Linear,
};

struct SamplerDesc {
    SamplerAddressMode address_mode_U = SamplerAddressMode::Repeat;
    SamplerAddressMode address_mode_V = SamplerAddressMode::Repeat;
    SamplerAddressMode address_mode_W = SamplerAddressMode::Repeat;
    SamplerFilter min_filter = SamplerFilter::Linear;
    SamplerFilter mag_filter = SamplerFilter::Linear;
    SamplerFilter mipmap_filter = SamplerFilter::Linear;
};

struct TextureDesc {
    TextureKind kind;
    DataFormat  format;
    TUInt       width;
    TUInt       height = 1;
    TUInt       depth  = 1;
    TUInt       mip_levels = 1;
    SamplerDesc sample_desc;
};

class ITexture : public IResource {
public:
    ResourceKind getResourceKind() const override final { return ResourceKind::Texture; }
    TextureKind  getTextureKind() const { return kind_; }
    DataFormat   getFormat() const { return format_; }

protected:
    ITexture(TextureKind kind, DataFormat format) : kind_(kind), format_(format) {}

private: 
    TextureKind kind_;
    DataFormat  format_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_TEXTURE_H_
