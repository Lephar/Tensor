#pragma once

#include "pch.h"

extern VkDescriptorSetLayout descriptorSetLayout;
extern VkPipelineLayout computePipelineLayout;
extern VkPipeline computePipeline;

void createComputePipeline();
void destroyComputePipeline();
