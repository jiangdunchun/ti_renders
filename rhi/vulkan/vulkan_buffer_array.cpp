#include "vulkan/vulkan_buffer_array.h"

#include "vulkan/vulkan_buffer.h"

namespace tigine { namespace rhi {
VulkanBufferArray::VulkanBufferArray(const BufferArrayDesc &desc) : index_kind_(desc.index_kind) {
    vertices_buffer_ = dynamic_cast<VulkanBuffer *>(desc.vertices_buffer);
    if (desc.indices_buffer) {
        indices_buffer_ = dynamic_cast<VulkanBuffer *>(desc.indices_buffer);
        has_indices_    = true;
    }

    size_t num_bindings = desc.bindings.size();
    vk_bindings_desc_.resize(num_bindings, {});
    for (size_t i = 0; i < num_bindings; ++i) {
        const BindingInfo &binding_info = desc.bindings[i];
        VkVertexInputBindingDescription &bindings_desc = vk_bindings_desc_[i];

        bindings_desc.binding   = binding_info.binding;
        bindings_desc.stride    = binding_info.stride;
        bindings_desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }

    size_t num_attributes = desc.attributes.size();
    vk_attributes_desc_.resize(num_attributes, {});
    for (size_t i = 0; i < num_attributes; ++i) {
        const AttributeInfo &attribute_info = desc.attributes[i];
        VkVertexInputAttributeDescription &attributes_desc = vk_attributes_desc_[i];

        attributes_desc.binding  = attribute_info.binding;
        attributes_desc.location = attribute_info.location;
        attributes_desc.format   = mapVkFormat(attribute_info.format);
        attributes_desc.offset   = attribute_info.offset;
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
