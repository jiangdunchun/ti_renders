#include "vulkan/vulkan_resource_heap.h"

#include <vector>
#include <stdexcept>

namespace tigine { namespace graphic {
namespace {
VkDescriptorType mapDescriptorType(IResource *resource) {
    ResourceKind kind = resource->getResourceKind();
    switch (kind) {
    case ResourceKind::Buffer:
        return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        break;
    case ResourceKind::Texture:
        return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        break;
    default:
        return VK_DESCRIPTOR_TYPE_MAX_ENUM;
        break;
    }
}

VkShaderStageFlags mapShaderStageFlags(ShaderKind kind) {
    switch (kind) {
    case ShaderKind::Vertex:
        return VK_SHADER_STAGE_VERTEX_BIT;
        break;
    case ShaderKind::Fragment:
        return VK_SHADER_STAGE_FRAGMENT_BIT;
        break;
    case ShaderKind::Compute:
        return VK_SHADER_STAGE_COMPUTE_BIT;
        break;
    default:
        return 0;
        break;
    }
}
} // namespace

VulkanResourceHeap::VulkanResourceHeap(VkDevice *device, const ResourceHeapDescriptor &desc) : device_(device) {
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    for (int i = 0; i < desc.uniforms_count; ++i) {
        UniformInfo &uniform = *(desc.uniforms + i);

        VkDescriptorSetLayoutBinding binding {};
        binding.binding            = uniform.binding;
        binding.descriptorCount    = 1;
        binding.descriptorType     = mapDescriptorType(uniform.resource);
        binding.pImmutableSamplers = nullptr;
        binding.stageFlags         = mapShaderStageFlags(uniform.shader_stage);

        bindings.push_back(binding);
    }
    VkDescriptorSetLayoutCreateInfo layout_info {};
    layout_info.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layout_info.bindingCount = static_cast<uint32_t>(bindings.size());
    layout_info.pBindings    = bindings.data();
    if (vkCreateDescriptorSetLayout(*device_, &layout_info, nullptr, &descriptor_set) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

VulkanResourceHeap::~VulkanResourceHeap() { vkDestroyDescriptorSetLayout(*device_, descriptor_set, nullptr); }
}} // namespace tigine::graphic