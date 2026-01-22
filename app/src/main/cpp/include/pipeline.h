#pragma once

#include "tensor.h"

extern VkShaderModule shaderModule;

extern VkDescriptorSetLayout descriptorSetLayout;
extern VkDescriptorPool descriptorPool;
extern VkDescriptorSet descriptorSet;

extern VkPipelineLayout pipelineLayout;
extern VkPipeline pipeline;

void createShaderModules();
void createDescriptorSet();
void createPipeline();

void destroyShaderModules();
void destroyDescriptorSet();
void destroyPipeline();
