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

uint32_t findMemoryType(VkPhysicalDevice *physical_device, uint32_t type_filter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties mem_properties;
    vkGetPhysicalDeviceMemoryProperties(*physical_device, &mem_properties);

    for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++) {
        if ((type_filter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    RHI_VULKAN_THROW("failed to find suitable memory type!");
}
} // namespace

bool            VulkanTexture::need_init_static_  = true;
VkCommandPool   VulkanTexture::vk_command_pool_   = {};
VkCommandBuffer VulkanTexture::vk_command_buffer_ = {};

VulkanTexture::VulkanTexture(const VulkanContextInfo &context, const TextureDesc &desc)
    : vk_physical_device_(context.vk_physical_device), vk_graphics_queue_(context.vk_graphics_queue), vk_device_(context.vk_device) {
    if (need_init_static_) {
        createVkCommandPoolandCommandBuffers(vk_device_, context.vk_graphics_family, 1, vk_command_pool_, &vk_command_buffer_);
        need_init_static_ = false;
    }

    VkImageCreateInfo image_info {};
    image_info.sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.imageType     = mapVkImageType(desc.kind);
    image_info.extent.width  = desc.texture_size.width;
    image_info.extent.height = desc.texture_size.height;
    image_info.extent.depth  = desc.texture_size.depth;
    image_info.mipLevels     = desc.mip_levels;
    image_info.arrayLayers   = desc.kind == TextureKind::TextureCube ? 6 : 1;
    image_info.format        = mapVkFormat(desc.format);
    image_info.tiling        = VK_IMAGE_TILING_OPTIMAL;
    image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    image_info.usage         = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    image_info.samples       = VK_SAMPLE_COUNT_1_BIT;
    image_info.sharingMode   = VK_SHARING_MODE_EXCLUSIVE;
    if (desc.kind == TextureKind::TextureCube) {
        image_info.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
    }
    RHI_VULKAN_THROW_IF_FAILD(vkCreateImage(*vk_device_, &image_info, nullptr, &vk_image_), "failed to create image!");

    VkMemoryRequirements mem_requirements {};
    vkGetImageMemoryRequirements(*vk_device_, vk_image_, &mem_requirements);
    VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    VkMemoryAllocateInfo  alloc_info {};
    alloc_info.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    alloc_info.allocationSize  = mem_requirements.size;
    alloc_info.memoryTypeIndex = findMemoryType(vk_physical_device_, mem_requirements.memoryTypeBits, properties);
    RHI_VULKAN_THROW_IF_FAILD(vkAllocateMemory(*vk_device_, &alloc_info, nullptr, &vk_device_memory_), "failed to allocate image memory!");

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
    RHI_VULKAN_THROW_IF_FAILD(vkCreateImageView(*vk_device_, &imageview_info, nullptr, &vk_imageview_), "failed to create image viewer!");

    VkPhysicalDeviceProperties device_properties {};
    vkGetPhysicalDeviceProperties(*vk_physical_device_, &device_properties);
    VkSamplerCreateInfo sampler_info {};
    sampler_info.sType                   = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
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
    RHI_VULKAN_THROW_IF_FAILD(vkCreateSampler(*vk_device_, &sampler_info, nullptr, &vk_sampler_), "failed to create sampler!");

    for (auto& data : desc.src_data) {
        updateData(data);
    }
}

VulkanTexture::~VulkanTexture() { 
    vkDestroySampler(*vk_device_, vk_sampler_, nullptr);
    vkDestroyImageView(*vk_device_, vk_imageview_, nullptr);
}

VkCommandBuffer beginSingleTimeCommands(VkDevice &device, VkCommandPool &commandPool) {
    VkCommandBufferAllocateInfo allocInfo {};
    allocInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool        = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}

void endSingleTimeCommands(VkQueue &graphicsQueue, VkDevice &device, VkCommandPool &commandPool, VkCommandBuffer &commandBuffer) {
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo {};
    submitInfo.sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers    = &commandBuffer;

    vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(graphicsQueue);

    vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

void transitionImageLayout(VkQueue                          &graphicsQueue,
                           VkDevice                         &device,
                           VkCommandPool &commandPool,
                            VkImage image,
                           VkFormat                          format,
                           VkImageLayout                     oldLayout,
                           VkImageLayout                     newLayout) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommands(device, commandPool);

    VkImageMemoryBarrier barrier {};
    barrier.sType                           = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout                       = oldLayout;
    barrier.newLayout                       = newLayout;
    barrier.srcQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
    barrier.image                           = image;
    barrier.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel   = 0;
    barrier.subresourceRange.levelCount     = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount     = 1;

    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;

    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        sourceStage      = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    } else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        sourceStage      = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    } else {
        throw std::invalid_argument("unsupported layout transition!");
    }

    vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

    endSingleTimeCommands(graphicsQueue, device, commandPool, commandBuffer);
}

void copyBufferToImage(VkQueue       &graphicsQueue,
                       VkDevice      &device,
                       VkCommandPool &commandPool,
                       VkBuffer       buffer,
                       VkImage        image,
                       uint32_t       width,
                       uint32_t       height) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommands(device, commandPool);

    VkBufferImageCopy region {};
    region.bufferOffset                    = 0;
    region.bufferRowLength                 = 0;
    region.bufferImageHeight               = 0;
    region.imageSubresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel       = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount     = 1;
    region.imageOffset                     = {0, 0, 0};
    region.imageExtent                     = {width, height, 1};

    vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

    endSingleTimeCommands(graphicsQueue, device, commandPool, commandBuffer);
}

void VulkanTexture::updateData(const TextureDataDesc &desc) {
    uint32_t       image_size = desc.data_size.width * desc.data_size.height * 4;
    VkBuffer       temp_buffer;
    VkDeviceMemory temp_memory;
    createVkBufferandDeviceMemory(vk_physical_device_,
                                  vk_device_,
                                  image_size,
                                  VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                  temp_buffer,
                                  temp_memory);

    void *temp_memory_ptr;
    vkMapMemory(*vk_device_, temp_memory, 0, image_size, 0, &temp_memory_ptr);
    memcpy(temp_memory_ptr, desc.data, static_cast<size_t>(image_size));
    vkUnmapMemory(*vk_device_, temp_memory);

    transitionImageLayout(*vk_graphics_queue_,
                          *vk_device_,
                          vk_command_pool_,
                          vk_image_,
                          VK_FORMAT_R8G8B8A8_SRGB,
                          VK_IMAGE_LAYOUT_UNDEFINED,
                          VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    copyBufferToImage(*vk_graphics_queue_,
                      *vk_device_,
                      vk_command_pool_,
                      temp_buffer,
                      vk_image_,
                      static_cast<uint32_t>(desc.data_size.width),
                      static_cast<uint32_t>(desc.data_size.height));
    transitionImageLayout(*vk_graphics_queue_,
                          *vk_device_,
                          vk_command_pool_,
                          vk_image_,
                          VK_FORMAT_R8G8B8A8_SRGB,
                          VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                          VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    vkDestroyBuffer(*vk_device_, temp_buffer, nullptr);
    vkFreeMemory(*vk_device_, temp_memory, nullptr);
}
}} // namespace tigine::rhi