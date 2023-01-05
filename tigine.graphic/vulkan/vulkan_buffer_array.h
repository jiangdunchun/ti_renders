#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_ARRAY_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_ARRAY_H_

#include "interface/i_buffer_array.h"

#include <vector>

#include "vulkan/vulkan_common.h"


namespace tigine { namespace graphic {
class VulkanBuffer;
class VulkanBufferArray : public IBufferArray {
public:
    VulkanBufferArray(const BufferArrayDescriptor &desc);
    ~VulkanBufferArray();

    VkPipelineVertexInputStateCreateInfo *getVkPipelineVertexInputStateCreateInfo() { return &vk_pipeline_vertex_input_state_create_info_; }

private:
    VulkanBuffer *vertices_buffer_;
    VulkanBuffer *indices_buffer_ = nullptr;

    VkPipelineVertexInputStateCreateInfo           vk_pipeline_vertex_input_state_create_info_;
    std::vector<VkVertexInputBindingDescription>   vk_bindings_desc_;
    std::vector<VkVertexInputAttributeDescription> vk_attributes_desc_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_ARRAY_H_
