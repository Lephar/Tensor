#pragma once

#include "pch.h"

extern VkDescriptorSetLayout descriptorSetLayout;
extern VkPipelineLayout pipelineLayout;

extern VkShaderModule shaderModule;
extern VkPipeline pipeline;

void createPipelineLayout();
void createShaderModules();
void createPipeline();

void destroyPipelineLayout();
void destroyShaderModules();
void destroyPipeline();
