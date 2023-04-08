#include "vulkan_common.h"

namespace tigine { namespace rhi {
namespace {
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

VkFormat mapVkFormat(DataFormat format) {
    switch (format) {
    case DataFormat::R8UNorm:
        return VK_FORMAT_R8_UNORM;
    case DataFormat::R8SNorm:
        return VK_FORMAT_R8_SNORM;
    case DataFormat::R8UInt:
        return VK_FORMAT_R8_UINT;
    case DataFormat::R8SInt:
        return VK_FORMAT_R8_SINT;

    case DataFormat::R16UNorm:
        return VK_FORMAT_R16_UNORM;
    case DataFormat::R16SNorm:
        return VK_FORMAT_R16_SNORM;
    case DataFormat::R16UInt:
        return VK_FORMAT_R16_UINT;
    case DataFormat::R16SInt:
        return VK_FORMAT_R16_SINT;
    case DataFormat::R16Float:
        return VK_FORMAT_R16_SFLOAT;

    case DataFormat::R32UInt:
        return VK_FORMAT_R32_UINT;
    case DataFormat::R32SInt:
        return VK_FORMAT_R32_SINT;
    case DataFormat::R32Float:
        return VK_FORMAT_R32_SFLOAT;

    case DataFormat::R64Float:
        return VK_FORMAT_R64_SFLOAT;

    case DataFormat::RG8UNorm:
        return VK_FORMAT_R8G8_UNORM;
    case DataFormat::RG8SNorm:
        return VK_FORMAT_R8G8_SNORM;
    case DataFormat::RG8UInt:
        return VK_FORMAT_R8G8_UINT;
    case DataFormat::RG8SInt:
        return VK_FORMAT_R8G8_SINT;

    case DataFormat::RG16UNorm:
        return VK_FORMAT_R16G16_UNORM;
    case DataFormat::RG16SNorm:
        return VK_FORMAT_R16G16_SNORM;
    case DataFormat::RG16UInt:
        return VK_FORMAT_R16G16_UINT;
    case DataFormat::RG16SInt:
        return VK_FORMAT_R16G16_SINT;
    case DataFormat::RG16Float:
        return VK_FORMAT_R16G16_SFLOAT;

    case DataFormat::RG32UInt:
        return VK_FORMAT_R32G32_UINT;
    case DataFormat::RG32SInt:
        return VK_FORMAT_R32G32_SINT;
    case DataFormat::RG32Float:
        return VK_FORMAT_R32G32_SFLOAT;

    case DataFormat::RG64Float:
        return VK_FORMAT_R64G64_SFLOAT;

    case DataFormat::RGB8UNorm:
        return VK_FORMAT_R8G8B8_UNORM;
    case DataFormat::RGB8UNorm_sRGB:
        return VK_FORMAT_R8G8B8_SRGB;
    case DataFormat::RGB8SNorm:
        return VK_FORMAT_R8G8B8_SNORM;
    case DataFormat::RGB8UInt:
        return VK_FORMAT_R8G8B8_UINT;
    case DataFormat::RGB8SInt:
        return VK_FORMAT_R8G8B8_SINT;

    case DataFormat::RGB16UNorm:
        return VK_FORMAT_R16G16B16_UNORM;
    case DataFormat::RGB16SNorm:
        return VK_FORMAT_R16G16B16_SNORM;
    case DataFormat::RGB16UInt:
        return VK_FORMAT_R16G16B16_UINT;
    case DataFormat::RGB16SInt:
        return VK_FORMAT_R16G16B16_SINT;
    case DataFormat::RGB16Float:
        return VK_FORMAT_R16G16B16_SFLOAT;

    case DataFormat::RGB32UInt:
        return VK_FORMAT_R32G32B32_UINT;
    case DataFormat::RGB32SInt:
        return VK_FORMAT_R32G32B32_SINT;
    case DataFormat::RGB32Float:
        return VK_FORMAT_R32G32B32_SFLOAT;

    case DataFormat::RGB64Float:
        return VK_FORMAT_R64G64B64_SFLOAT;

    case DataFormat::RGBA8UNorm:
        return VK_FORMAT_R8G8B8A8_UNORM;
    case DataFormat::RGBA8UNorm_sRGB:
        return VK_FORMAT_R8G8B8A8_SRGB;
    case DataFormat::RGBA8SNorm:
        return VK_FORMAT_R8G8B8A8_SNORM;
    case DataFormat::RGBA8UInt:
        return VK_FORMAT_R8G8B8A8_UINT;
    case DataFormat::RGBA8SInt:
        return VK_FORMAT_R8G8B8A8_SINT;

    case DataFormat::RGBA16UNorm:
        return VK_FORMAT_R16G16B16A16_UNORM;
    case DataFormat::RGBA16SNorm:
        return VK_FORMAT_R16G16B16A16_SNORM;
    case DataFormat::RGBA16UInt:
        return VK_FORMAT_R16G16B16A16_UINT;
    case DataFormat::RGBA16SInt:
        return VK_FORMAT_R16G16B16A16_SINT;
    case DataFormat::RGBA16Float:
        return VK_FORMAT_R16G16B16A16_SFLOAT;

    case DataFormat::RGBA32UInt:
        return VK_FORMAT_R32G32B32A32_UINT;
    case DataFormat::RGBA32SInt:
        return VK_FORMAT_R32G32B32A32_SINT;
    case DataFormat::RGBA32Float:
        return VK_FORMAT_R32G32B32A32_SFLOAT;

    case DataFormat::RGBA64Float:
        return VK_FORMAT_R64G64B64A64_SFLOAT;

    case DataFormat::BGRA8UNorm:
        return VK_FORMAT_B8G8R8A8_UNORM;
    case DataFormat::BGRA8UNorm_sRGB:
        return VK_FORMAT_B8G8R8A8_SRGB;
    case DataFormat::BGRA8SNorm:
        return VK_FORMAT_B8G8R8A8_SNORM;
    case DataFormat::BGRA8UInt:
        return VK_FORMAT_B8G8R8A8_UINT;
    case DataFormat::BGRA8SInt:
        return VK_FORMAT_B8G8R8A8_SINT;

    case DataFormat::RGB10A2UNorm:
        return VK_FORMAT_A2B10G10R10_UNORM_PACK32;
    case DataFormat::RGB10A2UInt:
        return VK_FORMAT_A2B10G10R10_UINT_PACK32;
    case DataFormat::RG11B10Float:
        return VK_FORMAT_B10G11R11_UFLOAT_PACK32;
    case DataFormat::RGB9E5Float:
        return VK_FORMAT_E5B9G9R9_UFLOAT_PACK32;

    case DataFormat::D16UNorm:
        return VK_FORMAT_D16_UNORM;
    case DataFormat::D32Float:
        return VK_FORMAT_D32_SFLOAT;
    case DataFormat::D24UNormS8UInt:
        return VK_FORMAT_D24_UNORM_S8_UINT;
    case DataFormat::D32FloatS8X24UInt:
        return VK_FORMAT_D32_SFLOAT_S8_UINT;

    case DataFormat::BC1UNorm:
        return VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
    case DataFormat::BC1UNorm_sRGB:
        return VK_FORMAT_BC1_RGBA_SRGB_BLOCK;
    case DataFormat::BC2UNorm:
        return VK_FORMAT_BC2_UNORM_BLOCK;
    case DataFormat::BC2UNorm_sRGB:
        return VK_FORMAT_BC2_SRGB_BLOCK;
    case DataFormat::BC3UNorm:
        return VK_FORMAT_BC3_UNORM_BLOCK;
    case DataFormat::BC3UNorm_sRGB:
        return VK_FORMAT_BC3_SRGB_BLOCK;
    case DataFormat::BC4UNorm:
        return VK_FORMAT_BC4_UNORM_BLOCK;
    case DataFormat::BC4SNorm:
        return VK_FORMAT_BC4_SNORM_BLOCK;
    case DataFormat::BC5UNorm:
        return VK_FORMAT_BC5_UNORM_BLOCK;
    case DataFormat::BC5SNorm:
        return VK_FORMAT_BC5_SNORM_BLOCK;
    }
    return VK_FORMAT_UNDEFINED;
}

void createVkBufferandDeviceMemory(VkPhysicalDevice     *physical_device,
                                   VkDevice             *device,
                                   VkDeviceSize          buffer_size,
                                   VkBufferUsageFlags    buffer_usage,
                                   VkMemoryPropertyFlags memory_property,
                                   VkBuffer             &o_buffer,
                                   VkDeviceMemory       &o_device_memory) {
    VkBufferCreateInfo buffer_create_info {};
    buffer_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buffer_create_info.size  = buffer_size;
    buffer_create_info.usage = buffer_usage;
    // @HACK
    // disable the multiple queue families' support
    // see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
    buffer_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    RHI_VULKAN_THROW_IF_FAILD(vkCreateBuffer(*device, &buffer_create_info, nullptr, &o_buffer), 
        "failed to create buffer!");


    VkMemoryRequirements memory_requirements;
    vkGetBufferMemoryRequirements(*device, o_buffer, &memory_requirements);
    uint32_t memory_type_index = findMemoryType(physical_device, memory_requirements.memoryTypeBits, memory_property);

    VkMemoryAllocateInfo memory_alloc_info {};
    memory_alloc_info.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memory_alloc_info.allocationSize  = memory_requirements.size;
    memory_alloc_info.memoryTypeIndex = memory_type_index;
    RHI_VULKAN_THROW_IF_FAILD(vkAllocateMemory(*device, &memory_alloc_info, nullptr, &o_device_memory),
        "failed to allocate buffer memory!");


    vkBindBufferMemory(*device, o_buffer, o_device_memory, 0);
}

void createVkCommandPoolandCommandBuffers(VkDevice        *device,
                                          uint32_t         queue_family_index,
                                          uint32_t         num_buffers,
                                          VkCommandPool   &o_command_pool,
                                          VkCommandBuffer *o_command_buffers) {
    VkCommandPoolCreateInfo pool_create_info {};
    pool_create_info.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pool_create_info.pNext            = nullptr;
    pool_create_info.flags            = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    pool_create_info.queueFamilyIndex = queue_family_index;
    RHI_VULKAN_THROW_IF_FAILD(vkCreateCommandPool(*device, &pool_create_info, nullptr, &o_command_pool),
       "failed to create command pool!");

    VkCommandBufferAllocateInfo buffer_alloc_info {};
    buffer_alloc_info.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    buffer_alloc_info.commandPool        = o_command_pool;
    buffer_alloc_info.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    buffer_alloc_info.commandBufferCount = num_buffers;
    RHI_VULKAN_THROW_IF_FAILD(vkAllocateCommandBuffers(*device, &buffer_alloc_info, o_command_buffers),
        "failed to allocate command buffer!");
}
}} // namespace tigine::rhi