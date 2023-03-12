#ifndef TIGINE_RHI_VULKAN_VULKAN_BUFFER_H_
#define TIGINE_RHI_VULKAN_VULKAN_BUFFER_H_

#include "interface/i_buffer.h"

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanBuffer : public IBuffer {
public:
    VulkanBuffer(VkPhysicalDevice *vk_physical_device, VkDevice *vk_device, const BufferDesc &desc);
    ~VulkanBuffer();
    virtual void updateData(TULong data_size, void *data) override;
    TUInt        getDataSize() { return data_size_; }
    VkBuffer    *getVkBuffer() { return &vk_buffer_; }

private:
    VkPhysicalDevice *vk_physical_divece_;
    VkDevice         *vk_device_;

    VkBuffer       vk_buffer_;
    VkDeviceMemory vk_device_memory_;

    TUInt          data_size_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_BUFFER_H_
