#include "pipeline.h"

#include "device.h"
#include "shader.h"

#include "logger.h"

VkDescriptorSetLayout descriptorSetLayout;
VkPipelineLayout computePipelineLayout;
VkPipeline computePipeline;

void createComputePipeline() {
    VkDescriptorSetLayoutBinding setLayoutBinding = {
        .binding = 0,
        .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        .descriptorCount = 1,
        .stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
        .pImmutableSamplers = nullptr
    };

    VkDescriptorSetLayoutCreateInfo setLayoutInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .bindingCount = 1,
        .pBindings = &setLayoutBinding
    };

    vkCreateDescriptorSetLayout(device, &setLayoutInfo, nullptr, &descriptorSetLayout);
    debug("Descriptor set layout created");

    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .setLayoutCount = 1,
        .pSetLayouts = &descriptorSetLayout,
        .pushConstantRangeCount = 0,
        .pPushConstantRanges = nullptr
    };

    vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &computePipelineLayout);
    debug("Compute pipeline layout created");

    VkComputePipelineCreateInfo pipelineInfo = {
        .sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .stage = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .stage = VK_SHADER_STAGE_COMPUTE_BIT,
            .module = computeShaderModule,
            .pName = "main",
            .pSpecializationInfo = nullptr
        },
        .layout = computePipelineLayout,
        .basePipelineHandle = VK_NULL_HANDLE,
        .basePipelineIndex = -1
    };

    vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &computePipeline);
    debug("Compute pipeline created");
}

void destroyComputePipeline() {
    vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
    debug("Descriptor set layout destroyed");

    vkDestroyPipelineLayout(device, computePipelineLayout, nullptr);
    debug("Compute pipeline layout destroyed");

    vkDestroyPipeline(device, computePipeline, nullptr);
    debug("Compute pipeline destroyed");
}
