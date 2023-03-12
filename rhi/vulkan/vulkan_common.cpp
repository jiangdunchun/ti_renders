#include "vulkan_common.h"

namespace tigine { namespace rhi {
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
}} // namespace tigine::rhi