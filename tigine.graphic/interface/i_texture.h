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

struct TextureDescriptor {
    TextureKind kind;
    TUShort     format;
    TUInt       width;
    TUInt       height = 1;
    TUInt       depth  = 1;
};

class ITexture : IResource {
public:
    ResourceKind getResourceKind() const override { return ResourceKind::Texture; }
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
