#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_H_

#include "interface/i_buffer.h"

#include "vulkan/vulkan_common.h"


namespace tigine { namespace graphic {
class VulkanBuffer : public IBuffer {
public:
    VulkanBuffer(VkPhysicalDevice *vk_physical_device, VkDevice *vk_device, const BufferDescriptor &desc);
    ~VulkanBuffer();
    virtual void updateData(TULong data_size, void *data) override;
    TUInt        getDataSize() { return data_size_; }
    VkBuffer    *getVkBuffer() { return &vk_buffer_; }

private:
    TUInt data_size_;

    VkPhysicalDevice *vk_physical_divece_;
    VkDevice         *vk_device_;

    VkBuffer       vk_buffer_;
    VkDeviceMemory vk_device_memory_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_H_
