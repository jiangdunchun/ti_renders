#include "vulkan/vulkan_texture.h"

#include <stdexcept>


namespace tigine { namespace graphic { 
namespace {
} // namespace

VulkanTexture::VulkanTexture(VkDevice *vk_device, const TextureDescriptor &desc) 
    : vk_device_(vk_device), ITexture(desc.kind, desc.format) {
    VkImageViewCreateInfo imageview_info {};
    imageview_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    // @TODO
    if (vkCreateImageView(*vk_device_, &imageview_info, nullptr, &vk_imageview_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture!");
    }

    VkSamplerCreateInfo sampler_info {};
    sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    // @TODO
    if (vkCreateSampler(*vk_device_, &sampler_info, nullptr, &vk_sampler_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture!");
    }
}

VulkanTexture::~VulkanTexture() { 
    vkDestroySampler(*vk_device_, vk_sampler_, nullptr);
    vkDestroyImageView(*vk_device_, vk_imageview_, nullptr);
}
}} // namespace tigine::graphic