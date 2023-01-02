#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_ARRAY_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_ARRAY_H_

#include <vector>

#include "interface/i_buffer_array.h"

#include "vulkan/vulkan_common.h"
#include "vulkan/vulkan_buffer.h"

namespace tigine { namespace graphic {
class VulkanBufferArray : public IBufferArray {
public:
    VulkanBufferArray(const BufferArrayDescriptor &desc);
    ~VulkanBufferArray();

    VkPipelineVertexInputStateCreateInfo getVertexInputInfo() { return vertex_input_info_; }

private:
    VulkanBuffer *vertices_buffer_;
    VulkanBuffer *indices_buffer_;
    VkPipelineVertexInputStateCreateInfo vertex_input_info_;
    std::vector<VkVertexInputBindingDescription> bindings_desc_;
    std::vector<VkVertexInputAttributeDescription> attributes_desc_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_ARRAY_H_
