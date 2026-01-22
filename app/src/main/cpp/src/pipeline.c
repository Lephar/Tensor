#include "pipeline.h"

#include "device.h"

#include "helper.h"

VkDescriptorSetLayout descriptorSetLayout;
VkPipelineLayout pipelineLayout;

VkShaderModule shaderModule;
VkPipeline pipeline;

VkShaderModule createShaderModule(const char *filename) {
    uint32_t *data = nullptr;
    size_t size = loadAsset(filename, (void **) &data);

    VkShaderModuleCreateInfo moduleInfo = {
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .codeSize = size,
            .pCode = data
    };

    VkShaderModule module;
    vkCreateShaderModule(device, &moduleInfo, nullptr, &module);
    free(data);

    return module;
}

void createShaderModules() {
    shaderModule = createShaderModule("shaders/tensor.comp.spv");
    debug("Shader modules created");
}

void createPipelineLayout() {
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

    vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout);
    debug("Pipeline layout created");
}

void createPipeline() {
    VkComputePipelineCreateInfo pipelineInfo = {
        .sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .stage = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .stage = VK_SHADER_STAGE_COMPUTE_BIT,
            .module = shaderModule,
            .pName = "main",
            .pSpecializationInfo = nullptr
        },
        .layout = pipelineLayout,
        .basePipelineHandle = VK_NULL_HANDLE,
        .basePipelineIndex = -1
    };

    vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline);
    debug("Pipeline created");
}

void destroyShaderModule(VkShaderModule module) {
    vkDestroyShaderModule(device, module, nullptr);
}

void destroyShaderModules() {
    destroyShaderModule(shaderModule);
    debug("Shader modules destroyed");
}

void destroyPipelineLayout() {
    vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
    debug("Descriptor set layout destroyed");

    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    debug("Pipeline layout destroyed");
}

void destroyPipeline() {
    vkDestroyPipeline(device, pipeline, nullptr);
    debug("Pipeline destroyed");
}
