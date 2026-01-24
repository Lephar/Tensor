#include "dispatch.h"

#include "device.h"
#include "pipeline.h"
#include "memory.h"

#include "helper.h"

void recordCommands() {
    VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext = nullptr,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
        .pInheritanceInfo = nullptr
    };

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
    vkCmdDispatch(commandBuffer, 2, 1, 1);

    vkEndCommandBuffer(commandBuffer);

    debug("Commands recorded");
}

void dispatch() {
    memset(mappedMemory, 0, bufferMemory.size);
    flushMemory(&bufferMemory);

    VkPipelineStageFlags waitStage = 0;

    VkSubmitInfo submitInfo = {
            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .pNext = nullptr,
            .waitSemaphoreCount = 0,
            .pWaitSemaphores = nullptr,
            .pWaitDstStageMask = &waitStage,
            .commandBufferCount = 1,
            .pCommandBuffers = &commandBuffer,
            .signalSemaphoreCount = 0,
            .pSignalSemaphores = nullptr,
    };

    vkQueueSubmit(queue, 1, &submitInfo, fence);
    debug("Commands dispatched");
}

void waitDispatch() {
    vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);
    vkResetFences(device, 1, &fence);
    debug("Dispatch finished");

    flushMemory(&bufferMemory);
    debug("Values:");
    for(int index = 0; index < 256; index++) {
        debug("%u", ((uint32_t *)mappedMemory)[index]);
    }
}
