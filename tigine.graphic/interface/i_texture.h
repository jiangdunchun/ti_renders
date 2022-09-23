#ifndef TIGINE_GRAPHIC_INTERFACE_I_TEXTURE_H_
#define TIGINE_GRAPHIC_INTERFACE_I_TEXTURE_H_

#include "interface/i_common.h"

namespace tigine { namespace graphic {
enum class TextureKind {
    Texture1D,
    Texture2D,
    Texture3D,
    TextureCube
};

struct TextureDescriptor {};

class ITexture {
public:
    TextureKind getTextureKind() const { return kind_; }
    TUShort     getFormat() const { return format_; }

private: 
    TextureKind kind_;
    TUShort     format_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_TEXTURE_H_
