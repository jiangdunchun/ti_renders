#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_H_

#include "vulkan/vulkan_common.h"
#include "interface/i_buffer.h"

namespace tigine { namespace graphic {
class VulkanBuffer : public IBuffer {
public:
    VulkanBuffer(const BufferDescriptor &desc, const void *data);
    ~VulkanBuffer();
    DISALLOW_COPY_AND_ASSIGN(VulkanBuffer);

    GLuint getID() const { return id_; }

private:
    GLuint id_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_H_
