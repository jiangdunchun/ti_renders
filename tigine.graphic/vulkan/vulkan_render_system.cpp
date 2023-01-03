#include "vulkan/vulkan_render_system.h"

#include <assert.h>

namespace tigine { namespace graphic {
VulkanRenderSystem::VulkanRenderSystem() { 
	command_queue_ = new VulkanCommandQueue();
}

VulkanRenderSystem::~VulkanRenderSystem() { 
	delete command_queue_;
}

IRenderContext *VulkanRenderSystem::createRenderContext(const RenderContextDescriptor &desc) { 
	VulkanRenderContext *render_context = new VulkanRenderContext(desc);

	vk_physicl_device_ = render_context->getVkPhysicalDevice();
    vk_device_         = render_context->getVklDevice();

	return render_context;
}

IShader *VulkanRenderSystem::createShader(const ShaderDescriptor &desc) { 
	assert(vk_device_);
    return new VulkanShader(vk_device_, desc);
}

IShaderProgram  *VulkanRenderSystem::createShaderProgram(const ShaderProgramDescriptor &desc) { 
	return new VulkanShaderProgram(desc);
}

IBuffer *VulkanRenderSystem::createBuffer(const BufferDescriptor &desc) { 
	assert(vk_physicl_device_ && vk_device_);
	return new VulkanBuffer(vk_physicl_device_, vk_device_, desc);
}

IBufferArray    *VulkanRenderSystem::createBufferArray(const BufferArrayDescriptor &desc) { return nullptr; }
ICommandQueue   *VulkanRenderSystem::getCommandQueue() { return command_queue_; }
ICommandBuffer  *VulkanRenderSystem::createCommandBuffer() { return nullptr; }
ITexture        *VulkanRenderSystem::createTexture(const TextureDescriptor &desc) { return nullptr; }
IResourceHeap   *VulkanRenderSystem::CreateResourceHeap(const ResourceHeapDescriptor &desc) { return nullptr; }
IRenderPass     *VulkanRenderSystem::CreateRenderPass(const RenderPassDescriptor &desc) { return nullptr; }
IRenderTarget   *VulkanRenderSystem::createRenderTarget(const RenderTargetDescriptor &desc) { return nullptr; }
IPipelineLayout *VulkanRenderSystem::createPipelineLayout(const PipelineLayoutDescriptor &desc) { return nullptr; }
IPipelineState  *VulkanRenderSystem::createPipelineState(const PipelineStateDescriptor &desc) { return nullptr; }
}} // namespace tigine::graphic
