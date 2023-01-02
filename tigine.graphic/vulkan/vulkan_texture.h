#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_TEXTURE_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_TEXTURE_H_

#include "vulkan/vulkan_common.h"
#include "interface/i_texture.h"

namespace tigine { namespace graphic {
class VulkanTexture : public ITexture {
public:
    VulkanTexture(VkDevice *device, const TextureDescriptor &desc);
    ~VulkanTexture();

    VkImageView *getImageview() { return &imageview_; }
    VkSampler   *getSampler() { return &sampler_; }

private:
    VkDevice   *device_;
    VkImageView imageview_;
    VkSampler   sampler_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_TEXTURE_H_
