#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_H_

#include "vulkan/vulkan_common.h"
#include "interface/i_buffer.h"

namespace tigine { namespace graphic {
class VulkanBuffer : public IBuffer {
public:
    VulkanBuffer(VkPhysicalDevice *physical_divece, VkDevice * device, const BufferDescriptor &desc);
    ~VulkanBuffer();
    virtual void updateData(TULong data_size, void *data) override;
    TUInt        getDataSize() { return data_size_; }
    VkBuffer    *getVkBuffer() { return &buffer_; }

private:
    TUInt             data_size_;
    VkPhysicalDevice *physical_divece_;
    VkDevice         *device_;
    VkBuffer          buffer_;
    VkDeviceMemory    memory_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_H_
