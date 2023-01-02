#include "vulkan/vulkan_buffer_array.h"

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

VulkanBufferArray::VulkanBufferArray(const BufferArrayDescriptor &desc) 
	: vertices_buffer_(desc.vertices_buffer), indices_buffer_(desc.indices_buffer) {
    bindings_desc_.resize(desc.bindings_count);
    for (int i = 0; i < desc.bindings_count; ++i) {
        BindingInfo &binding_info = *(desc.bindings + i);

        bindings_desc_[i].binding   = binding_info.binding;
        bindings_desc_[i].stride    = binding_info.stride;
        bindings_desc_[i].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }
    vertex_input_info_.vertexBindingDescriptionCount = static_cast<uint32_t>(bindings_desc_.size());
    vertex_input_info_.pVertexBindingDescriptions    = bindings_desc_.data();

    attributes_desc_.resize(desc.attributes_count);
    for (int i = 0; i < desc.attributes_count; ++i) {
        AttributeInfo &attribute_info = *(desc.attributes + i);

        attributes_desc_[i].binding  = attribute_info.binding;
        attributes_desc_[i].location = attribute_info.location;
        attributes_desc_[i].format   = mapDataFormat(attribute_info.format);
        attributes_desc_[i].offset   = attribute_info.offset;
    }
    vertex_input_info_.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributes_desc_.size());
    vertex_input_info_.pVertexAttributeDescriptions    = attributes_desc_.data();
}

VulkanBufferArray::~VulkanBufferArray() {}
}} // namespace tigine::graphic
