#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_RESOURCE_HEAP_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_RESOURCE_HEAP_H_

#include "vulkan/vulkan_common.h"
#include "interface/i_resource_heap.h"
namespace tigine { namespace graphic {
class VulkanResourceHeap : public IResourceHeap {
public:
    VulkanResourceHeap(VkDevice *device, const ResourceHeapDescriptor &desc);
    ~VulkanResourceHeap();
    VkDescriptorSetLayout *getDescriptorSetLayout() { return &descriptor_set; }

private:
    VkDevice             *device_;
    VkDescriptorSetLayout descriptor_set;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_RESOURCE_HEAP_H_