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
#include "vulkan/vulkan_render_pass.h"
#include "vulkan/vulkan_render_target.h"

namespace tigine { namespace rhi {
VulkanRenderSystem::VulkanRenderSystem() {}
	

VulkanRenderSystem::~VulkanRenderSystem() { 
	delete command_queue_;
}

IRenderContext *VulkanRenderSystem::createRenderContext(const RenderContextDesc &desc) { 
	VulkanRenderContext *render_context = new VulkanRenderContext(desc, context_info_);

	command_queue_ = new VulkanCommandQueue(context_info_);

	return render_context;
}

IShader *VulkanRenderSystem::createShader(const ShaderDesc &desc) { 
    return new VulkanShader(context_info_, desc); }

IShaderProgram *VulkanRenderSystem::createShaderProgram(const ShaderProgramDesc &desc) { 
	return new VulkanShaderProgram(context_info_, desc);
}

IBuffer *VulkanRenderSystem::createBuffer(const BufferDesc &desc) { 
	return new VulkanBuffer(context_info_, desc);
}

IBufferArray *VulkanRenderSystem::createBufferArray(const BufferArrayDesc &desc) { 
	return new VulkanBufferArray(context_info_, desc);
}

ICommandQueue *VulkanRenderSystem::getCommandQueue() { return command_queue_; }

ICommandBuffer *VulkanRenderSystem::createCommandBuffer(const CommandBufferDesc &desc) { 
    return new VulkanCommandBuffer(context_info_, desc);
}

ITexture *VulkanRenderSystem::createTexture(const TextureDesc &desc) { 
	return new VulkanTexture(context_info_, desc); }

IResourceHeap  *VulkanRenderSystem::CreateResourceHeap(const ResourceHeapDesc &desc) {
	return new VulkanResourceHeap(context_info_, desc);
}

IRenderPass *VulkanRenderSystem::CreateRenderPass(const RenderPassDesc &desc) { 
	return new VulkanRenderPass(context_info_, desc);
}

IRenderTarget *VulkanRenderSystem::createRenderTarget(const RenderTargetDesc &desc) { 
	return new VulkanRenderTarget(context_info_, desc);
}

IPipelineState  *VulkanRenderSystem::createPipelineState(const PipelineStateDesc &desc) { 
	return new VulkanPipelineState(context_info_, desc);
}

}} // namespace tigine::rhi
