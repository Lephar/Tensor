#pragma once

#include "tensor.h"

typedef struct memory {
    VkMemoryPropertyFlags properties;
    uint32_t typeIndex;
    VkDeviceSize size;
    VkDeviceSize offset;
    VkDeviceMemory memory;
} Memory, *PMemory;

typedef struct buffer {
    VkBufferUsageFlags usage;
    VkDeviceSize size;
    VkBuffer buffer;
    VkMemoryRequirements memoryRequirements;
    VkDeviceSize memoryOffset;
    Memory *memory;
} Buffer, *PBuffer;

extern Memory bufferMemory;
extern void *mappedMemory;

extern Buffer storageBuffer;

void allocateMemories();
void createBuffers();

void flushMemory(Memory *memory);

void destroyBuffers();
void freeMemories();
