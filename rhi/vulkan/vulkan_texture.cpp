#include "vulkan/vulkan_texture.h"

namespace tigine { namespace rhi { 
namespace {
VkImageType mapVkImageType(TextureKind kind) {
    switch (kind) {
    case TextureKind::Texture1D:
        return VK_IMAGE_TYPE_1D;
    case TextureKind::Texture2D:
    case TextureKind::TextureCube:
        return VK_IMAGE_TYPE_2D;
    case TextureKind::Texture3D:
        return VK_IMAGE_TYPE_3D;
    default:
        RHI_VULKAN_THROW("failed to map ImageType!");
    }
}

uint32_t findMemoryType(VkPhysicalDevice *physical_divece, uint32_t type_filter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties mem_properties;
    vkGetPhysicalDeviceMemoryProperties(*physical_divece, &mem_properties);

    for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++) {
        if ((type_filter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    RHI_VULKAN_THROW("failed to find suitable memory type!");
}
} // namespace

VulkanTexture::VulkanTexture(VkPhysicalDevice *vk_physical_device, VkDevice *vk_device, const TextureDesc &desc) 
    : vk_physical_device_(vk_physical_device), vk_device_(vk_device), ITexture(desc.kind, desc.format) {
    VkImageCreateInfo image_info {};
    image_info.sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.imageType     = mapVkImageType(desc.kind);
    image_info.extent.width  = desc.width;
    image_info.extent.height = desc.height;
    image_info.extent.depth  = desc.depth;
    image_info.mipLevels     = desc.mip_levels;
    image_info.arrayLayers   = desc.kind == TextureKind::TextureCube? 6 : 1;
    image_info.format        = mapVkFormat(desc.format);
    image_info.tiling        = VK_IMAGE_TILING_OPTIMAL;
    image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    image_info.usage         = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    image_info.samples       = VK_SAMPLE_COUNT_1_BIT;
    image_info.sharingMode   = VK_SHARING_MODE_EXCLUSIVE;
    if (desc.kind == TextureKind::TextureCube) {
        image_info.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
    }
    RHI_VULKAN_THROW_IF_FAILD(vkCreateImage(*vk_device_, &image_info, nullptr, &vk_image_), 
        "failed to create image!");

    VkMemoryRequirements mem_requirements {};
    vkGetImageMemoryRequirements(*vk_device_, vk_image_, &mem_requirements);
    VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    VkMemoryAllocateInfo alloc_info {};
    alloc_info.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    alloc_info.allocationSize  = mem_requirements.size;
    alloc_info.memoryTypeIndex = findMemoryType(vk_physical_device_, mem_requirements.memoryTypeBits, properties);
    RHI_VULKAN_THROW_IF_FAILD(vkAllocateMemory(*vk_device_, &alloc_info, nullptr, &vk_device_memory_),
        "failed to allocate image memory!");

    vkBindImageMemory(*vk_device_, vk_image_, vk_device_memory_, 0);

    VkImageViewCreateInfo imageview_info {};
    imageview_info.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageview_info.image                           = vk_image_;
    imageview_info.viewType                        = VK_IMAGE_VIEW_TYPE_2D; // @TODO
    imageview_info.format                          = mapVkFormat(desc.format);
    imageview_info.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    imageview_info.subresourceRange.baseMipLevel   = 0;
    imageview_info.subresourceRange.levelCount     = 1;
    imageview_info.subresourceRange.baseArrayLayer = 0;
    imageview_info.subresourceRange.layerCount     = 1;
    RHI_VULKAN_THROW_IF_FAILD(vkCreateImageView(*vk_device_, &imageview_info, nullptr, &vk_imageview_),
        "failed to create image viewer!");

    VkPhysicalDeviceProperties device_properties {};
    vkGetPhysicalDeviceProperties(*vk_physical_device_, &device_properties);
    VkSamplerCreateInfo sampler_info {};
    sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sampler_info.sType                   = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sampler_info.magFilter               = VK_FILTER_LINEAR;
    sampler_info.minFilter               = VK_FILTER_LINEAR;
    sampler_info.addressModeU            = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_info.addressModeV            = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_info.addressModeW            = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_info.anisotropyEnable        = VK_TRUE;
    sampler_info.maxAnisotropy           = device_properties.limits.maxSamplerAnisotropy;
    sampler_info.borderColor             = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    sampler_info.unnormalizedCoordinates = VK_FALSE;
    sampler_info.compareEnable           = VK_FALSE;
    sampler_info.compareOp               = VK_COMPARE_OP_ALWAYS;
    sampler_info.mipmapMode              = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    RHI_VULKAN_THROW_IF_FAILD(vkCreateSampler(*vk_device_, &sampler_info, nullptr, &vk_sampler_),
        "failed to create sampler!");
}

VulkanTexture::~VulkanTexture() { 
    vkDestroySampler(*vk_device_, vk_sampler_, nullptr);
    vkDestroyImageView(*vk_device_, vk_imageview_, nullptr);
}

void VulkanTexture::updateData(TULong data_size, void *data, TUInt mip_level) {

}
}} // namespace tigine::rhi