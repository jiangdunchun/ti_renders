#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_RESOURCE_HEAP_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_RESOURCE_HEAP_H_

#include "vulkan/vulkan_common.h"
#include "interface/i_resource_heap.h"
namespace tigine { namespace graphic {
class VulkanResourceHeap : public IResourceHeap {
public:
    VulkanResourceHeap(VkDevice *device, const ResourceHeapDescriptor &desc);
    ~VulkanResourceHeap();
    VkDescriptorSetLayout *getVKDescriptorSetLayout() { return &vk_descriptor_set_layout_; }

private:
    VkDevice             *vk_device_;
    VkDescriptorSetLayout vk_descriptor_set_layout_;
    VkDescriptorPool      vk_descriptor_pool_;
    VkDescriptorSet       vk_descriptor_set_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_RESOURCE_HEAP_H_