#include "memory.h"

#include "device.h"
#include "buffer.h"

#include "numerics.h"
#include "logger.h"

Memory bufferMemory;
void *mappedMemory;

VkDeviceSize alignMemory(Memory *memory, VkMemoryRequirements memoryRequirements) {
    VkDeviceSize bindOffset = align(memory->offset, memoryRequirements.alignment);

    memory->offset = bindOffset + memoryRequirements.size;

    return bindOffset;
}

void allocateMemory(Memory *memory, uint32_t typeFilter, VkMemoryPropertyFlags requiredProperties, VkDeviceSize size) {
    memory->properties = requiredProperties;
    memory->typeIndex = UINT32_MAX;
    memory->offset = 0;
    memory->size = size;

    for(uint32_t memoryIndex = 0; memoryIndex < memoryProperties.memoryTypeCount; memoryIndex++) {
        if((typeFilter & (1 << memoryIndex)) && (memoryProperties.memoryTypes[memoryIndex].propertyFlags & requiredProperties) == requiredProperties) {
            memory->typeIndex = memoryIndex; // TODO: Implement an actual logic
            break;
        }
    }

    assert(memory->typeIndex < memoryProperties.memoryTypeCount);

    /* TODO: Why doesn't this work?
    if(memory->size > memoryProperties.memoryHeaps[memoryProperties.memoryTypes[memory->typeIndex].heapIndex].size) {
        memory->size = memoryProperties.memoryHeaps[memoryProperties.memoryTypes[memory->typeIndex].heapIndex].size;
    } */

    while(memory->size > memoryProperties.memoryHeaps[memoryProperties.memoryTypes[memory->typeIndex].heapIndex].size) {
        memory->size /= 2;
    } // TODO: Take used memory into account

    VkMemoryAllocateInfo memoryInfo = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .pNext = nullptr,
        .allocationSize = memory->size,
        .memoryTypeIndex = memory->typeIndex
    };

    vkAllocateMemory(device, &memoryInfo, nullptr, &memory->memory);
}

void *mapMemory(Memory *memory) {
    assert(memory->memory != VK_NULL_HANDLE);
    assert(memory->properties & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

    void *map;
    vkMapMemory(device, memory->memory, 0, VK_WHOLE_SIZE, 0, &map);
    return map;
}

void allocateMemories() {
    Buffer temporaryBuffer;
    createBuffer(&temporaryBuffer, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, 1L << 20L);

    VkMemoryRequirements bufferMemoryRequirements;
    vkGetBufferMemoryRequirements(device, temporaryBuffer.buffer, &bufferMemoryRequirements);

    uint32_t typeFilter = bufferMemoryRequirements.memoryTypeBits;
    destroyBuffer(&temporaryBuffer);

    debug("Buffer memory:");
    // TODO: Syntax highlighting fails for %b but it compiles, contribute to clangd maybe?
    debug("\tSuitable type indices:\t%08b", typeFilter);

    allocateMemory(&bufferMemory, typeFilter, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, 1L << 30L);

    debug("\tSelected type index:\t%u", bufferMemory.typeIndex);
    debug("\t%ld bytes allocated", bufferMemory.size);

    mappedMemory = mapMemory(&bufferMemory);
    debug("\tSuccessfully mapped");
}

void unmapMemory(Memory *memory) {
    vkUnmapMemory(device, memory->memory);
}

void freeMemory(Memory *memory) {
    vkFreeMemory(device, memory->memory, nullptr);

    memory->properties = 0;
    memory->typeIndex = UINT32_MAX;
    memory->size = 0;
    memory->offset = 0;
}

void freeMemories() {
    unmapMemory(&bufferMemory);
    freeMemory(&bufferMemory);
    debug("Compute memory freed");
}
