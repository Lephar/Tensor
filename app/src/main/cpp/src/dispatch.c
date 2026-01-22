#include "dispatch.h"

#include "device.h"
#include "pipeline.h"

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
    vkCmdDispatch(commandBuffer, 4, 8, 16);

    vkEndCommandBuffer(commandBuffer);

    debug("Commands recorded");
}

void dispatch() {
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

    vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);

    debug("Commands dispatched");
}

void waitDispatch() {
    debug("Dispatch finished");
}
