#ifndef TIGINE_RHI_VULKAN_VULKAN_BUFFER_H_
#define TIGINE_RHI_VULKAN_VULKAN_BUFFER_H_

#include "interface/i_buffer.h"

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanBuffer : public IBuffer {
public:
    VulkanBuffer(const VulkanContextInfo& context, const BufferDesc &desc);
    ~VulkanBuffer();

    virtual void updateData(const BufferDataDesc &desc) override;

    TUInt     getDataSize() { return buffer_size_; }
    VkBuffer    *getVkBuffer() { return &vk_buffer_; }

private:
    VkDevice *vk_device_;

    VkBuffer       vk_buffer_;
    VkDeviceMemory vk_device_memory_;
    TUInt          buffer_size_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_BUFFER_H_
