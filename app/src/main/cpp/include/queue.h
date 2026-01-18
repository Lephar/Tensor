#pragma once

#include "pch.h"

typedef struct queue {
    VkQueueFlags requiredFlags;
    uint32_t queueFamilyIndex;
    uint32_t queueIndex;
    uint32_t queueInfoIndex;
    VkQueue queue;
    VkCommandPool commandPool;
} Queue, *PQueue;

extern uint32_t distinctQueueFamilyCount;
extern VkDeviceQueueCreateInfo *queueInfos;

extern Queue computeQueue;

extern uint32_t queueCount;
extern Queue *queueReferences[];

void generateQueueDetails();
void getQueues();
VkCommandBuffer allocateSingleCommandBuffer(Queue *queue);
VkCommandBuffer beginSingleComputeCommand();
void endSingleComputeCommand(VkCommandBuffer commandBuffer);
void clearQueues();
