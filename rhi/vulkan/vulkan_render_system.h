#ifndef TIGINE_RHI_VULKAN_VULKAN_RENDER_SYSTEM_H_
#define TIGINE_RHI_VULKAN_VULKAN_RENDER_SYSTEM_H_

#include "interface/i_render_system.h"

#include "vulkan/vulkan_common.h"


namespace tigine { namespace rhi {
class VulkanCommandQueue;
class VulkanRenderSystem : public IRenderSystem {
public:
    VulkanRenderSystem();
    ~VulkanRenderSystem();

    IRenderContext *createRenderContext(const RenderContextDesc &desc) override;
    IShader        *createShader(const ShaderDesc &desc) override;
    IShaderProgram *createShaderProgram(const ShaderProgramDesc &desc) override;
    IBuffer        *createBuffer(const BufferDesc &desc) override;
    IBufferArray   *createBufferArray(const BufferArrayDesc &desc) override;
    ICommandQueue  *getCommandQueue() override;
    ICommandBuffer *createCommandBuffer(const CommandBufferDesc &desc) override;
    ITexture       *createTexture(const TextureDesc &desc) override;
    IResourceHeap  *CreateResourceHeap(const ResourceHeapDesc &desc) override;
    IRenderPass    *CreateRenderPass(const RenderPassDesc &desc) override;
    IRenderTarget  *createRenderTarget(const RenderTargetDesc &desc) override;
    IPipelineState *createPipelineState(const PipelineStateDesc &desc) override;

private:
    VkPhysicalDevice *vk_physicl_device_  = nullptr;
    VkDevice         *vk_device_          = nullptr;
    VkQueue          *vk_graphics_queue_  = nullptr;
    uint32_t          vk_graphics_family_ = 0;

    VulkanCommandQueue *command_queue_ = nullptr;
    

};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_RENDER_SYSTEM_H_
