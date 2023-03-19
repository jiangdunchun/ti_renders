#include "vulkan/vulkan_render_system.h"

#include "vulkan/vulkan_command_queue.h"
#include "vulkan/vulkan_buffer.h"
#include "vulkan/vulkan_buffer_array.h"
#include "vulkan/vulkan_command_buffer.h"
#include "vulkan/vulkan_pipeline_state.h"
#include "vulkan/vulkan_render_context.h"
#include "vulkan/vulkan_shader.h"
#include "vulkan/vulkan_shader_program.h"
#include "vulkan/vulkan_resource_heap.h"
#include "vulkan/vulkan_texture.h"

namespace tigine { namespace rhi {
VulkanRenderSystem::VulkanRenderSystem() {}
	

VulkanRenderSystem::~VulkanRenderSystem() { 
	delete command_queue_;
}

IRenderContext *VulkanRenderSystem::createRenderContext(const RenderContextDesc &desc) { 
	VulkanRenderContext *render_context = new VulkanRenderContext(desc);

	vk_physicl_device_  = render_context->getVkPhysicalDevice();
    vk_device_          = render_context->getVklDevice();
    vk_graphics_queue_  = render_context->getVkGraphicsQueue();
    vk_graphics_family_ = render_context->getVkGraphicsFamily();

	command_queue_ = new VulkanCommandQueue(vk_graphics_queue_);

	return render_context;
}

IShader *VulkanRenderSystem::createShader(const ShaderDesc &desc) { 
    return new VulkanShader(vk_device_, desc);
}

IShaderProgram  *VulkanRenderSystem::createShaderProgram(const ShaderProgramDesc &desc) { 
	return new VulkanShaderProgram(desc);
}

IBuffer *VulkanRenderSystem::createBuffer(const BufferDesc &desc) { 
	return new VulkanBuffer(vk_physicl_device_, vk_device_, desc);
}

IBufferArray *VulkanRenderSystem::createBufferArray(const BufferArrayDesc &desc) { 
	return new VulkanBufferArray(desc);
}

ICommandQueue   *VulkanRenderSystem::getCommandQueue() { return command_queue_; }

ICommandBuffer *VulkanRenderSystem::createCommandBuffer(const CommandBufferDesc &desc) { 
    return new VulkanCommandBuffer(vk_device_, vk_graphics_queue_, vk_graphics_family_, desc);
}

ITexture *VulkanRenderSystem::createTexture(const TextureDesc &desc) { 
	return new VulkanTexture(vk_physicl_device_, vk_graphics_queue_, vk_graphics_family_, vk_device_, desc);
}

IResourceHeap  *VulkanRenderSystem::CreateResourceHeap(const ResourceHeapDesc &desc) {
	return new VulkanResourceHeap(vk_device_, desc);
}

IRenderPass     *VulkanRenderSystem::CreateRenderPass(const RenderPassDesc &desc) { return nullptr; }

IRenderTarget   *VulkanRenderSystem::createRenderTarget(const RenderTargetDesc &desc) { return nullptr; }

IPipelineState  *VulkanRenderSystem::createPipelineState(const PipelineStateDesc &desc) { 
	return new VulkanPipelineState(vk_device_, desc);
}

}} // namespace tigine::rhi
