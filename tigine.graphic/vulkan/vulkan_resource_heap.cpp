#include "vulkan/vulkan_resource_heap.h"

#include <vector>
#include <stdexcept>

#include "Vulkan/vulkan_buffer.h"
#include "vulkan/vulkan_texture.h"


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

VulkanResourceHeap::VulkanResourceHeap(VkDevice *vk_device, const ResourceHeapDescriptor &desc) : vk_device_(vk_device) {
    std::vector<VkDescriptorSetLayoutBinding> bindings(desc.uniforms_count);
    for (int i = 0; i < desc.uniforms_count; ++i) {
        UniformInfo &uniform = *(desc.uniforms + i);

        VkDescriptorSetLayoutBinding &binding = bindings[i];

        binding.binding            = uniform.binding;
        binding.descriptorCount    = 1;
        binding.descriptorType     = mapDescriptorType(uniform.resource);
        binding.pImmutableSamplers = nullptr;
        binding.stageFlags         = mapShaderStageFlags(uniform.shader_stage);
    }

    VkDescriptorSetLayoutCreateInfo layout_info {};
    layout_info.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layout_info.bindingCount = static_cast<uint32_t>(bindings.size());
    layout_info.pBindings    = bindings.data();
    if (vkCreateDescriptorSetLayout(*vk_device_, &layout_info, nullptr, &vk_descriptor_set_layout_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }


    std::vector<VkDescriptorPoolSize> pool_sizes(desc.uniforms_count);
    for (int i = 0; i < desc.uniforms_count; ++i) {
        UniformInfo &uniform = *(desc.uniforms + i);

        VkDescriptorPoolSize &pool_size = pool_sizes[i];

        pool_size.type            = mapDescriptorType(uniform.resource);
        pool_size.descriptorCount = 1;
    }

    VkDescriptorPoolCreateInfo pool_info {};
    pool_info.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.poolSizeCount = static_cast<uint32_t>(pool_sizes.size());
    pool_info.pPoolSizes    = pool_sizes.data();
    pool_info.maxSets       = 1;
    if (vkCreateDescriptorPool(*vk_device_, &pool_info, nullptr, &vk_descriptor_pool_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }


    VkDescriptorSetAllocateInfo alloc_info {};
    alloc_info.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    alloc_info.descriptorPool     = vk_descriptor_pool_;
    alloc_info.descriptorSetCount = 1;
    alloc_info.pSetLayouts        = &vk_descriptor_set_layout_;
    if (vkAllocateDescriptorSets(*vk_device_, &alloc_info, &vk_descriptor_set_) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }


    std::vector<VkWriteDescriptorSet> writes(desc.uniforms_count);
    for (int i = 0; i < desc.uniforms_count; ++i) {
        UniformInfo &uniform = *(desc.uniforms + i);

        VkWriteDescriptorSet &write = writes[i];

        write.sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        write.dstSet          = vk_descriptor_set_;
        write.dstBinding      = 0;
        write.dstArrayElement = 0;
        write.descriptorType  = mapDescriptorType(uniform.resource);
        write.descriptorCount = 1;

        if (uniform.resource->getResourceKind() == ResourceKind::Buffer) {
            VulkanBuffer *vulkan_buffer = static_cast<VulkanBuffer *>(uniform.resource);

            VkDescriptorBufferInfo buffer_info {};
            buffer_info.buffer = *(vulkan_buffer->getVkBuffer());
            buffer_info.offset = 0;
            buffer_info.range  = vulkan_buffer->getDataSize();

            write.pBufferInfo = &buffer_info;
        } else if (uniform.resource->getResourceKind() == ResourceKind::Texture) {
            VulkanTexture *vulkan_texture = static_cast<VulkanTexture *>(uniform.resource);

            VkDescriptorImageInfo image_info {};
            image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            image_info.imageView   = *(vulkan_texture->getVKImageview());
            image_info.sampler     = *(vulkan_texture->getVKSampler());

            write.pImageInfo = &image_info;
        }
    }
    vkUpdateDescriptorSets(*vk_device_, static_cast<uint32_t>(writes.size()), writes.data(), 0, nullptr);


    VkPipelineLayoutCreateInfo pipeline_layout_info {};
    pipeline_layout_info.sType          = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_info.setLayoutCount = 1;
    pipeline_layout_info.pSetLayouts    = &vk_descriptor_set_layout_;
    if (vkCreatePipelineLayout(*vk_device_, &pipeline_layout_info, nullptr, &vk_pipeline_layout_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout!");
    }
}

VulkanResourceHeap::~VulkanResourceHeap() { 
    vkDestroyPipelineLayout(*vk_device_, vk_pipeline_layout_, nullptr);
    vkFreeDescriptorSets(*vk_device_, vk_descriptor_pool_, 1, &vk_descriptor_set_);
    vkDestroyDescriptorPool(*vk_device_, vk_descriptor_pool_, nullptr);
    vkDestroyDescriptorSetLayout(*vk_device_, vk_descriptor_set_layout_, nullptr);
}
}} // namespace tigine::graphic