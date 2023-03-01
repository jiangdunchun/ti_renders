#include "vulkan/vulkan_pipeline_state.h"

#include <stdexcept>

#include "vulkan/vulkan_shader_program.h"
#include "vulkan/vulkan_buffer_array.h"
#include "vulkan/vulkan_render_pass.h"
#include "vulkan/vulkan_resource_heap.h"


namespace tigine { namespace graphic {
VulkanPipelineState::VulkanPipelineState(VkDevice *vk_device, const PipelineStateDesc &desc) : vk_device_(vk_device) {
    VulkanShaderProgram *shader_prog    = dynamic_cast<VulkanShaderProgram *>(desc.shader_program);
    VulkanBufferArray   *vertices_array = dynamic_cast<VulkanBufferArray *>(desc.vertices_array);
    VulkanResourceHeap  *resource_heap  = dynamic_cast<VulkanResourceHeap *>(desc.resource_heap);
    VulkanRenderPass    *render_pass    = dynamic_cast<VulkanRenderPass *>(desc.render_pass);

    VkPipelineInputAssemblyStateCreateInfo inputAssembly {};
    inputAssembly.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport {};
    viewport.x        = 0.0f;
    viewport.y        = 0.0f;
    viewport.width    = 600;
    viewport.height   = 600;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor {};
    scissor.offset = {0, 0};
    scissor.extent = {600, 600};

    VkPipelineViewportStateCreateInfo viewportState {};
    viewportState.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports    = &viewport;
    viewportState.scissorCount  = 1;
    viewportState.pScissors     = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer {};
    rasterizer.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable        = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode             = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth               = 1.0f;
    rasterizer.cullMode                = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace               = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable         = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multisampling {};
    multisampling.sType                = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable  = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState colorBlendAttachment {};
    colorBlendAttachment.colorWriteMask
        = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlending {};
    colorBlending.sType             = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable     = VK_FALSE;
    colorBlending.logicOp           = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount   = 1;
    colorBlending.pAttachments      = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    VkGraphicsPipelineCreateInfo pipeline_info {};
    pipeline_info.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_info.stageCount          = shader_prog->getVKShaderStageCreateInfosCount();
    pipeline_info.pStages             = shader_prog->getVKShaderStageCreateInfos();
    pipeline_info.pVertexInputState   = vertices_array->getVkPipelineVertexInputStateCreateInfo();
    pipeline_info.pInputAssemblyState = &inputAssembly;
    pipeline_info.pViewportState      = &viewportState;
    pipeline_info.pRasterizationState = &rasterizer;
    pipeline_info.pMultisampleState   = &multisampling;
    pipeline_info.pColorBlendState    = &colorBlending;
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
