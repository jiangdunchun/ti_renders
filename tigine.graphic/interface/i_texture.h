#ifndef TIGINE_GRAPHIC_INTERFACE_I_TEXTURE_H_
#define TIGINE_GRAPHIC_INTERFACE_I_TEXTURE_H_

#include "interface/i_common.h"
#include "interface/i_resource.h"

namespace tigine { namespace graphic {
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

struct SamplerDescriptor {
    SamplerAddressMode address_mode_U = SamplerAddressMode::Repeat;
    SamplerAddressMode address_mode_V = SamplerAddressMode::Repeat;
    SamplerAddressMode address_mode_W = SamplerAddressMode::Repeat;
    SamplerFilter min_filter = SamplerFilter::Linear;
    SamplerFilter mag_filter = SamplerFilter::Linear;
    SamplerFilter mipmap_filter = SamplerFilter::Linear;
    bool mipmapping = true;
};

struct TextureDescriptor {
    TextureKind kind;
    TUShort     format;
    TUInt       width;
    TUInt       height = 1;
    TUInt       depth  = 1;
    SamplerDescriptor sample_desc;
};

class ITexture : public IResource {
public:
    ResourceKind getResourceKind() const override final { return ResourceKind::Texture; }
    TextureKind  getTextureKind() const { return kind_; }
    TUShort      getFormat() const { return format_; }

protected:
    ITexture(TextureKind kind, TUShort format) : kind_(kind), format_(format) {}

private: 
    TextureKind kind_;
    TUShort     format_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_TEXTURE_H_
