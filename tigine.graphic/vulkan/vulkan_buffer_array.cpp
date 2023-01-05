#include "vulkan/vulkan_buffer_array.h"

#include "vulkan/vulkan_buffer.h"


namespace tigine { namespace graphic {
namespace {
VkFormat mapDataFormat(DataFormat format) {
    switch (format) {
    case (DF_RGB32Float):
        return VK_FORMAT_R32G32B32_SFLOAT;
        break;
    default:
        return VK_FORMAT_UNDEFINED;
        break;
    }
}
} // namespace

VulkanBufferArray::VulkanBufferArray(const BufferArrayDescriptor &desc) {
    vertices_buffer_ = static_cast<VulkanBuffer *>(desc.vertices_buffer);
    if (desc.indices_buffer) indices_buffer_ = static_cast<VulkanBuffer *>(desc.indices_buffer);


    vk_bindings_desc_.resize(desc.bindings_count);
    for (int i = 0; i < desc.bindings_count; ++i) {
        BindingInfo &binding_info = *(desc.bindings + i);

        vk_bindings_desc_[i].binding   = binding_info.binding;
        vk_bindings_desc_[i].stride    = binding_info.stride;
        vk_bindings_desc_[i].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }

    vk_attributes_desc_.resize(desc.attributes_count);
    for (int i = 0; i < desc.attributes_count; ++i) {
        AttributeInfo &attribute_info = *(desc.attributes + i);

        vk_attributes_desc_[i].binding  = attribute_info.binding;
        vk_attributes_desc_[i].location = attribute_info.location;
        vk_attributes_desc_[i].format   = mapDataFormat(attribute_info.format);
        vk_attributes_desc_[i].offset   = attribute_info.offset;
    }

    vk_pipeline_vertex_input_state_create_info_.vertexBindingDescriptionCount   = static_cast<uint32_t>(vk_bindings_desc_.size());
    vk_pipeline_vertex_input_state_create_info_.pVertexBindingDescriptions      = vk_bindings_desc_.data();
    vk_pipeline_vertex_input_state_create_info_.vertexAttributeDescriptionCount = static_cast<uint32_t>(vk_attributes_desc_.size());
    vk_pipeline_vertex_input_state_create_info_.pVertexAttributeDescriptions    = vk_attributes_desc_.data();
}

VulkanBufferArray::~VulkanBufferArray() {}
}} // namespace tigine::graphic
