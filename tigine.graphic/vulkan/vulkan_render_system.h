#ifndef TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_SYSTEM_H_
#define TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_SYSTEM_H_

#include "interface/i_render_system.h"

#include "vulkan/vulkan_common.h"


namespace tigine { namespace graphic {
class VulkanCommandQueue;
class VulkanRenderSystem : public IRenderSystem {
public:
    VulkanRenderSystem();
    ~VulkanRenderSystem();

    IRenderContext *createRenderContext(const RenderContextDescriptor &desc) override;
    IShader        *createShader(const ShaderDescriptor &desc) override;
    IShaderProgram *createShaderProgram(const ShaderProgramDescriptor &desc) override;
    IBuffer        *createBuffer(const BufferDescriptor &desc) override;
    IBufferArray   *createBufferArray(const BufferArrayDescriptor &desc) override;
    ICommandQueue  *getCommandQueue() override;
    ICommandBuffer *createCommandBuffer(const CommandBufferDescriptor &desc) override;
    ITexture       *createTexture(const TextureDescriptor &desc) override;
    IResourceHeap  *CreateResourceHeap(const ResourceHeapDescriptor &desc) override;
    IRenderPass    *CreateRenderPass(const RenderPassDescriptor &desc) override;
    IRenderTarget  *createRenderTarget(const RenderTargetDescriptor &desc) override;
    IPipelineState *createPipelineState(const PipelineStateDescriptor &desc) override;

private:
    VkPhysicalDevice *vk_physicl_device_ = nullptr;
    VkDevice         *vk_device_         = nullptr;

    VulkanCommandQueue *command_queue_ = nullptr;
    

};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_VULKAN_VULKAN_RENDER_SYSTEM_H_
