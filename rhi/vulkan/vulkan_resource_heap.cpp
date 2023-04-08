#include "vulkan/vulkan_resource_heap.h"

#include <vector>

#include "Vulkan/vulkan_buffer.h"
#include "vulkan/vulkan_texture.h"

namespace tigine { namespace rhi {
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
        RHI_VULKAN_THROW("fail to map DescriptorType!");
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
        RHI_VULKAN_THROW("fail to map ShaderStageFlags!");
    }
}
} // namespace

VulkanResourceHeap::VulkanResourceHeap(const VulkanContextInfo &context, const ResourceHeapDesc &desc) : vk_device_(context.vk_device) {
    size_t num_uniforms = desc.uniforms.size();

    std::vector<VkDescriptorSetLayoutBinding> bindings(num_uniforms);
    for (size_t i = 0; i < num_uniforms; ++i) {
        const UniformDesc            &uniform    = desc.uniforms[i];
        VkDescriptorSetLayoutBinding &vk_binding = bindings[i];

        vk_binding.binding            = static_cast<uint32_t>(uniform.binding);
        vk_binding.descriptorCount    = 1;
        vk_binding.descriptorType     = mapDescriptorType(uniform.resource);
        vk_binding.pImmutableSamplers = nullptr;
        vk_binding.stageFlags         = mapShaderStageFlags(uniform.shader_stage);
    }

    VkDescriptorSetLayoutCreateInfo vk_layout_info {};
    vk_layout_info.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    vk_layout_info.bindingCount = static_cast<uint32_t>(bindings.size());
    vk_layout_info.pBindings    = bindings.data();
    RHI_VULKAN_THROW_IF_FAILD(vkCreateDescriptorSetLayout(*vk_device_, &vk_layout_info, nullptr, &vk_descriptor_set_layout_),
        "failed to create descriptor set layout!");


    std::vector<VkDescriptorPoolSize> vk_pool_sizes(num_uniforms);
    for (size_t i = 0; i < num_uniforms; ++i) {
        const UniformDesc    &uniform   = desc.uniforms[i];
        VkDescriptorPoolSize &vk_pool_size = vk_pool_sizes[i];

        vk_pool_size.type            = mapDescriptorType(uniform.resource);
        vk_pool_size.descriptorCount = 1;
    }

    VkDescriptorPoolCreateInfo vk_pool_info {};
    vk_pool_info.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    vk_pool_info.poolSizeCount = static_cast<uint32_t>(vk_pool_sizes.size());
    vk_pool_info.pPoolSizes    = vk_pool_sizes.data();
    vk_pool_info.maxSets       = 1;
    RHI_VULKAN_THROW_IF_FAILD(vkCreateDescriptorPool(*vk_device_, &vk_pool_info, nullptr, &vk_descriptor_pool_),
        "failed to create descriptor pool!");


    VkDescriptorSetAllocateInfo vk_alloc_info {};
    vk_alloc_info.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    vk_alloc_info.descriptorPool     = vk_descriptor_pool_;
    vk_alloc_info.descriptorSetCount = 1;
    vk_alloc_info.pSetLayouts        = &vk_descriptor_set_layout_;
    RHI_VULKAN_THROW_IF_FAILD(vkAllocateDescriptorSets(*vk_device_, &vk_alloc_info, &vk_descriptor_set_),
        "failed to allocate descriptor sets!");


    std::vector<VkWriteDescriptorSet> vk_writes(num_uniforms);
    for (size_t i = 0; i < num_uniforms; ++i) {
        const UniformDesc    &uniform  = desc.uniforms[i];
        VkWriteDescriptorSet &vk_write = vk_writes[i];

        vk_write.sType        = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        vk_write.dstSet       = vk_descriptor_set_;
        vk_write.dstBinding   = static_cast<uint32_t>(uniform.binding);
        vk_write.dstArrayElement = 0;
        vk_write.descriptorType  = mapDescriptorType(uniform.resource);
        vk_write.descriptorCount = 1;

        if (uniform.resource->getResourceKind() == ResourceKind::Buffer) {
            VulkanBuffer *vulkan_buffer            = dynamic_cast<VulkanBuffer *>(uniform.resource);
            VkDescriptorBufferInfo *vk_buffer_info = new VkDescriptorBufferInfo({});

            vk_buffer_info->buffer = *(vulkan_buffer->getVkBuffer());
            vk_buffer_info->offset = 0;
            vk_buffer_info->range  = static_cast<VkDeviceSize>(vulkan_buffer->getBufferSize());

            vk_write.pBufferInfo = vk_buffer_info;
        } else if (uniform.resource->getResourceKind() == ResourceKind::Texture) {
            VulkanTexture *vulkan_texture     = dynamic_cast<VulkanTexture *>(uniform.resource);
            VkDescriptorImageInfo *vk_image_info = new VkDescriptorImageInfo({});

            vk_image_info->imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            vk_image_info->imageView   = *(vulkan_texture->getVKImageview());
            vk_image_info->sampler     = *(vulkan_texture->getVKSampler());

            vk_write.pImageInfo = vk_image_info;
        }
    }
    vkUpdateDescriptorSets(*vk_device_, static_cast<uint32_t>(vk_writes.size()), vk_writes.data(), 0, nullptr);
    for (size_t i = 0; i < num_uniforms; ++i) {
        VkWriteDescriptorSet &vk_write = vk_writes[i];
        if (vk_write.pBufferInfo) delete vk_write.pBufferInfo;
        if (vk_write.pImageInfo) delete vk_write.pImageInfo;
    }


    VkPipelineLayoutCreateInfo vk_pipeline_layout_info {};
    vk_pipeline_layout_info.sType          = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    vk_pipeline_layout_info.setLayoutCount = 1;
    vk_pipeline_layout_info.pSetLayouts    = &vk_descriptor_set_layout_;
    RHI_VULKAN_THROW_IF_FAILD(vkCreatePipelineLayout(*vk_device_, &vk_pipeline_layout_info, nullptr, &vk_pipeline_layout_),
        "failed to create pipeline layout!");
}

VulkanResourceHeap::~VulkanResourceHeap() { 
    vkDestroyPipelineLayout(*vk_device_, vk_pipeline_layout_, nullptr);
    vkFreeDescriptorSets(*vk_device_, vk_descriptor_pool_, 1, &vk_descriptor_set_);
    vkDestroyDescriptorPool(*vk_device_, vk_descriptor_pool_, nullptr);
    vkDestroyDescriptorSetLayout(*vk_device_, vk_descriptor_set_layout_, nullptr);
}
}} // namespace tigine::rhi