#include "vulkan/vulkan_texture.h"

#include <stdexcept>

namespace tigine { namespace graphic { 
namespace {
} // namespace

VulkanTexture::VulkanTexture(VkDevice *device, const TextureDescriptor &desc) : device_(device), ITexture(desc.kind, desc.format) {
    VkImageViewCreateInfo imageview_info {};
    imageview_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

    // @TODO

    if (vkCreateImageView(*device_, &imageview_info, nullptr, &imageview_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture!");
    }

    VkSamplerCreateInfo sampler_info {};
    sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;

    // @TODO

    if (vkCreateSampler(*device_, &sampler_info, nullptr, &sampler_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture!");
    }
}

VulkanTexture::~VulkanTexture() { 
    vkDestroySampler(*device_, sampler_, nullptr);
    vkDestroyImageView(*device_, imageview_, nullptr);
}
}} // namespace tigine::graphic