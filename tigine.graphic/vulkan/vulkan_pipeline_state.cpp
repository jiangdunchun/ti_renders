#include "vulkan/vulkan_pipeline_state.h"

#include <stdexcept>

#include "vulkan/vulkan_shader_program.h"
#include "vulkan/vulkan_buffer_array.h"
#include "vulkan/vulkan_render_pass.h"
#include "vulkan/vulkan_resource_heap.h"


namespace tigine { namespace graphic {
VulkanPipelineState::VulkanPipelineState(VkDevice* vk_device, const PipelineStateDescriptor& desc) {
    VulkanShaderProgram *shader_prog = static_cast<VulkanShaderProgram *>(desc.shader_program);
    VulkanBufferArray   *vertices_array = static_cast<VulkanBufferArray *>(desc.vertices_array);
    VulkanResourceHeap  *resource_heap  = static_cast<VulkanResourceHeap *>(desc.resource_heap);
    VulkanRenderPass    *render_pass    = static_cast<VulkanRenderPass *>(desc.render_pass);

    VkGraphicsPipelineCreateInfo pipeline_info {};
    pipeline_info.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_info.stageCount          = shader_prog->getVKShaderStageCreateInfosCount();
    pipeline_info.pStages             = shader_prog->getVKShaderStageCreateInfos();
    pipeline_info.pVertexInputState   = vertices_array->getVkPipelineVertexInputStateCreateInfo();
    //pipeline_info.pInputAssemblyState = &inputAssembly;
    //pipeline_info.pViewportState      = &viewportState;
    //pipeline_info.pRasterizationState = &rasterizer;
    //pipeline_info.pMultisampleState   = &multisampling;
    //pipeline_info.pColorBlendState    = &colorBlending;
    pipeline_info.layout              = *(resource_heap->getVkPipelineLayout());
    pipeline_info.renderPass          = *(render_pass->getVkRenderPass());
    pipeline_info.subpass             = 0;
    pipeline_info.basePipelineHandle  = VK_NULL_HANDLE;
    if (vkCreateGraphicsPipelines(*vk_device_, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &vk_pipeline_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics pipeline!");
    }
}

VulkanPipelineState::~VulkanPipelineState() { 
    vkDestroyPipeline(*vk_device_, vk_pipeline_, nullptr);
}
}} // namespace tigine::graphic
