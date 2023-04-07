#ifndef TIGINE_RHI_INTERFACE_I_TEXTURE_H_
#define TIGINE_RHI_INTERFACE_I_TEXTURE_H_

#include "interface/i_common.h"
#include "interface/i_resource.h"

namespace tigine { namespace rhi {
struct Extent3D {
    TUInt width  = 1;
    TUInt height = 1;
    TUInt depth  = 1;
};

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
    SamplerAddressMode address_mode_U;
    SamplerAddressMode address_mode_V;
    SamplerAddressMode address_mode_W;
    SamplerFilter      min_filter;
    SamplerFilter      mag_filter;
    SamplerFilter      mipmap_filter;
};

struct TextureDataDesc {
    DataFormat format;
    Extent3D   texture_size;
    void      *data;
    TUInt      array_layer = 0;
    TUInt      mip_level = 0;
};

struct TextureDesc {
    TextureKind     kind;
    DataFormat      format;
    Extent3D        texture_size;
    TUInt           mip_levels  = 1;
    SamplerDesc     sample_desc = {
        SamplerAddressMode::Repeat,
        SamplerAddressMode::Repeat,
        SamplerAddressMode::Repeat,
        SamplerFilter::Linear,
        SamplerFilter::Linear,
        SamplerFilter::Linear
    };
    TextureDataDesc data_desc   = { DataFormat::Undefined, { 0, 0, 0 }, nullptr };
};

class ITexture : public IResource {
public:
    virtual ~ITexture() = default;

    ResourceKind getResourceKind() const override final { return ResourceKind::Texture; }

    virtual void updateData(const TextureDataDesc &desc) = 0;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_TEXTURE_H_
