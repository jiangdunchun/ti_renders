#include "vulkan/vulkan_buffer_array.h"

#include "vulkan/vulkan_buffer.h"

namespace tigine { namespace rhi {
VulkanBufferArray::VulkanBufferArray(const VulkanContextInfo &context, const BufferArrayDesc &desc) {
    vertices_buffer_ = dynamic_cast<VulkanBuffer *>(desc.vertices_buffer);
    if (desc.indices_buffer) {
        indices_buffer_ = dynamic_cast<VulkanBuffer *>(desc.indices_buffer);
        index_kind_     = desc.index_kind;
        has_indices_    = true;
    }

    size_t num_bindings = desc.bindings.size();
    vk_bindings_desc_.resize(num_bindings, {});
    for (size_t i = 0; i < num_bindings; ++i) {
        const BindingDesc               &binding_desc    = desc.bindings[i];
        VkVertexInputBindingDescription &vk_binding_desc = vk_bindings_desc_[i];

        vk_binding_desc.binding   = static_cast<uint32_t>(binding_desc.binding);
        vk_binding_desc.stride    = static_cast<uint32_t>(binding_desc.stride);
        vk_binding_desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }

    size_t num_attributes = desc.attributes.size();
    vk_attributes_desc_.resize(num_attributes, {});
    for (size_t i = 0; i < num_attributes; ++i) {
        const AttributeDesc               &attribute_desc    = desc.attributes[i];
        VkVertexInputAttributeDescription &vk_attribute_desc = vk_attributes_desc_[i];

        vk_attribute_desc.binding  = static_cast<uint32_t>(attribute_desc.binding);
        vk_attribute_desc.location = static_cast<uint32_t>(attribute_desc.location);
        vk_attribute_desc.format   = mapVkFormat(attribute_desc.format);
        vk_attribute_desc.offset   = static_cast<uint32_t>(attribute_desc.offset);
    }

    vk_pipeline_vertex_input_state_create_info_                                 = {};
    vk_pipeline_vertex_input_state_create_info_.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vk_pipeline_vertex_input_state_create_info_.vertexBindingDescriptionCount   = static_cast<uint32_t>(vk_bindings_desc_.size());
    vk_pipeline_vertex_input_state_create_info_.pVertexBindingDescriptions      = vk_bindings_desc_.data();
    vk_pipeline_vertex_input_state_create_info_.vertexAttributeDescriptionCount = static_cast<uint32_t>(vk_attributes_desc_.size());
    vk_pipeline_vertex_input_state_create_info_.pVertexAttributeDescriptions    = vk_attributes_desc_.data();
}

VulkanBufferArray::~VulkanBufferArray() {}
}} // namespace tigine::rhi
