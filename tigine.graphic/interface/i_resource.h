#ifndef TIGINE_GRAPHIC_INTERFACE_I_RESOURCE_H_
#define TIGINE_GRAPHIC_INTERFACE_I_RESOURCE_H_

namespace tigine { namespace graphic {
enum class ResourceKind {
    Buffer,
    Texture,
    Sampler 
};

class IResource {
public:
    virtual ResourceKind getResourceKind() const = 0;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_RESOURCE_H_
