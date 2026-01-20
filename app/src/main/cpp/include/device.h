#pragma once

#include "pch.h"

extern VkPhysicalDevice physicalDevice;

extern uint32_t queueFamilyIndex;
extern VkQueueFamilyProperties queueFamilyProperties;

extern VkPhysicalDeviceProperties physicalDeviceProperties;
extern VkPhysicalDeviceFeatures physicalDeviceFeatures;

extern VkPhysicalDeviceMemoryProperties memoryProperties;

extern VkDevice device;

extern VkQueue queue;
extern VkCommandPool commandPool;

void selectPhysicalDevice();
void *loadDeviceFunction(const char *name);
void createDevice();
VkCommandBuffer allocateSingleCommandBuffer();
void beginSingleCommand(VkCommandBuffer commandBuffer);
void endSingleCommand(VkCommandBuffer commandBuffer);
void destroyDevice();
