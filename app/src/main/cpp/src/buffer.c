#include "buffer.h"

#include "device.h"
#include "queue.h"
#include "memory.h"

#include "numerics.h"
#include "logger.h"

Buffer storageBuffer;

void createBuffer(Buffer *buffer, VkBufferUsageFlags usage, VkDeviceSize size)
{
    buffer->usage = usage;
    buffer->size = size;

    VkBufferCreateInfo bufferInfo = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .size = size,
        .usage = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = nullptr
    };

    vkCreateBuffer(device, &bufferInfo, nullptr, &buffer->buffer);
    vkGetBufferMemoryRequirements(device, buffer->buffer, &buffer->memoryRequirements);
}

void bindBufferMemory(Buffer *buffer, Memory *memory) {
    buffer->memory = memory;
    buffer->memoryOffset = alignMemory(memory, buffer->memoryRequirements);

    vkBindBufferMemory(device, buffer->buffer, memory->memory, buffer->memoryOffset);
}

void createBuffers() {
    createBuffer(&storageBuffer, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, bufferMemory.size);
    bindBufferMemory(&storageBuffer, &bufferMemory);
    debug("Storage buffer created: %ld bytes", storageBuffer.size);
}

void destroyBuffer(Buffer *buffer) {
    vkDestroyBuffer(device, buffer->buffer, nullptr);

    buffer->memory = nullptr;
}

void destroyBuffers() {
    destroyBuffer(&storageBuffer);
    debug("Storage buffer destroyed");
}
