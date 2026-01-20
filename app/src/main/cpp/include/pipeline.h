#pragma once

#include "pch.h"

extern VkDescriptorSetLayout descriptorSetLayout;
extern VkPipelineLayout pipelineLayout;
extern VkPipeline pipeline;

void createPipeline();
void destroyPipeline();
