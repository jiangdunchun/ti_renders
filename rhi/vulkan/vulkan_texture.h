#ifndef TIGINE_RHI_VULKAN_VULKAN_TEXTURE_H_
#define TIGINE_RHI_VULKAN_VULKAN_TEXTURE_H_

#include "interface/i_texture.h"

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanTexture : public ITexture {
public:
    VulkanTexture(VkPhysicalDevice *vk_physical_device,
                  VkQueue          *vk_graphics_queue,
                  uint32_t          vk_queue_family_index, 
                  VkDevice         *vk_device,
                  const TextureDesc &desc);
    ~VulkanTexture();

    virtual void updateData(TUInt width, TUInt height, DataFormat formate, void *data, TUInt mip_level = 0) override;

    VkImageView *getVKImageview() { return &vk_imageview_; }
    VkSampler   *getVKSampler() { return &vk_sampler_; }

private:
    VkPhysicalDevice *vk_physical_device_;
    VkQueue          *vk_graphics_queue_;
    VkDevice         *vk_device_;

    static bool            need_init_static_;
    static VkCommandPool   vk_command_pool_;
    static VkCommandBuffer vk_command_buffer_;

    VkImage        vk_image_;
    VkDeviceMemory vk_device_memory_;
    VkImageView    vk_imageview_;
    VkSampler      vk_sampler_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_TEXTURE_H_
