#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_ARRAY_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_ARRAY_H_

#include <vector>

#include "vulkan/vulkan_common.h"
#include "interface/i_buffer_array.h"

namespace tigine { namespace graphic {
class VulkanBufferArray : public IBufferArray {
public:
    explicit VulkanBufferArray(const BufferArrayDescriptor &desc);
    ~VulkanBufferArray();

    GLuint getID() const { return id_; }

private:
    GLuint id_;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_BUFFER_ARRAY_H_
