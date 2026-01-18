#pragma once

#include "pch.h"

typedef struct memory Memory;

typedef struct buffer {
    VkBufferUsageFlags usage;
    VkDeviceSize size;
    VkBuffer buffer;
    VkMemoryRequirements memoryRequirements;
    VkDeviceSize memoryOffset;
    Memory *memory;
} Buffer, *PBuffer;

extern Buffer storageBuffer;

void createBuffers();
void destroyBuffers();

void createBuffer(Buffer *buffer, VkBufferUsageFlags usage, VkDeviceSize size);
void bindBufferMemory(Buffer *buffer, Memory *memory);
void destroyBuffer(Buffer *buffer);
