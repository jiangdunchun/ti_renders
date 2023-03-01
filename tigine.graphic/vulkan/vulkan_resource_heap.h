#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_RESOURCE_HEAP_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_RESOURCE_HEAP_H_

#include "interface/i_resource_heap.h"

#include "vulkan/vulkan_common.h"


namespace tigine { namespace graphic {
class VulkanResourceHeap : public IResourceHeap {
public:
    VulkanResourceHeap(VkDevice *vk_device, const ResourceHeapDesc &desc);
    ~VulkanResourceHeap();

    VkPipelineLayout *getVkPipelineLayout() { return &vk_pipeline_layout_; }

private:
    VkDevice *vk_device_;

    VkDescriptorSetLayout vk_descriptor_set_layout_;
    VkDescriptorPool      vk_descriptor_pool_;
    VkDescriptorSet       vk_descriptor_set_; 
    VkPipelineLayout      vk_pipeline_layout_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_RESOURCE_HEAP_H_