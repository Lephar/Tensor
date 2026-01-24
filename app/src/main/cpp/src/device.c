#include "device.h"

#include "instance.h"

#include "helper.h"

VkPhysicalDevice physicalDevice;

uint32_t queueFamilyIndex;
VkQueueFamilyProperties queueFamilyProperties;

VkPhysicalDeviceProperties physicalDeviceProperties;
VkPhysicalDeviceFeatures physicalDeviceFeatures;

VkPhysicalDeviceMemoryProperties memoryProperties;

VkDevice device;

PFN_vkGetDeviceProcAddr deviceFunctionLoader;

VkQueue queue;
VkCommandPool commandPool;
VkCommandBuffer commandBuffer;
VkFence fence;

void selectPhysicalDevice() {
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
    VkPhysicalDevice physicalDevices[physicalDeviceCount];
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices);

    for(uint32_t candidatePhysicalDeviceIndex = 0; candidatePhysicalDeviceIndex < physicalDeviceCount; candidatePhysicalDeviceIndex++) {
        VkPhysicalDevice candidatePhysicalDevice = physicalDevices[candidatePhysicalDeviceIndex];

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties2(candidatePhysicalDevice, &queueFamilyCount, nullptr);

        VkQueueFamilyProperties2 queueFamiliesProperties2[queueFamilyCount] = {};

        for(uint32_t candidateQueueFamilyIndex = 0; candidateQueueFamilyIndex < queueFamilyCount; candidateQueueFamilyIndex++) {
            queueFamiliesProperties2[candidateQueueFamilyIndex].sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
        }

        vkGetPhysicalDeviceQueueFamilyProperties2(candidatePhysicalDevice, &queueFamilyCount, queueFamiliesProperties2);

        for(uint32_t candidateQueueFamilyIndex = 0; candidateQueueFamilyIndex < queueFamilyCount; candidateQueueFamilyIndex++) {
            VkQueueFamilyProperties candidateQueueFamilyProperties = queueFamiliesProperties2[candidateQueueFamilyIndex].queueFamilyProperties;

            if(candidateQueueFamilyProperties.queueFlags & VK_QUEUE_COMPUTE_BIT) {
                physicalDevice = candidatePhysicalDevice;
                queueFamilyIndex = candidateQueueFamilyIndex;
                queueFamilyProperties = candidateQueueFamilyProperties;

                VkPhysicalDeviceProperties2 physicalDeviceProperties2 = {
                        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
                        .pNext = nullptr,
                        .properties = {}
                };

                vkGetPhysicalDeviceProperties2(physicalDevice, &physicalDeviceProperties2);
                physicalDeviceProperties = physicalDeviceProperties2.properties;

                VkPhysicalDeviceFeatures2 physicalDeviceFeatures2 = {
                        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
                        .pNext = nullptr,
                        .features = {}
                };

                vkGetPhysicalDeviceFeatures2(physicalDevice, &physicalDeviceFeatures2);
                physicalDeviceFeatures = physicalDeviceFeatures2.features;

                VkPhysicalDeviceMemoryProperties2 memoryProperties2 = {
                        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2,
                        .pNext = nullptr,
                        .memoryProperties = {}
                };

                vkGetPhysicalDeviceMemoryProperties2(physicalDevice, &memoryProperties2);
                memoryProperties = memoryProperties2.memoryProperties;

                debug("Physical device selected:");
                debug("\tName: %s", physicalDeviceProperties.deviceName);
                debug("\tQueue family index: %u", queueFamilyIndex);

                return;
            }
        }
    }

    assert(0);
}


void *loadDeviceFunction(const char *name) {
    void  *deviceFunction = deviceFunctionLoader(device, name);
    assert(deviceFunction);
    return deviceFunction;
}

void createDevice() {
    const char *extensions[] = {};

    uint32_t extensionCount = sizeof(extensions) / sizeof(const char *);

    debug("Device extensions (count = %d):", extensionCount);
    for(uint32_t index = 0; index < extensionCount; index++) {
        debug("\t%s", extensions[index]);
    }

    float queuePriority = 1.0f;

    VkDeviceQueueCreateInfo queueInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .queueFamilyIndex = queueFamilyIndex,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority
    };

    VkPhysicalDeviceVulkan11Features version11Features = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES,
        .pNext = nullptr,
    };

    VkPhysicalDeviceFeatures2 physicalDeviceFeatures2 = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
        .pNext = &version11Features,
        .features = {},
    };

    VkDeviceCreateInfo deviceInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = &physicalDeviceFeatures2,
        .flags = 0,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueInfo,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount = extensionCount,
        .ppEnabledExtensionNames = extensions,
        .pEnabledFeatures = nullptr,
    };

    vkCreateDevice(physicalDevice, &deviceInfo, nullptr, &device);
    debug("Device created");

    PFN_vkGetDeviceProcAddr instanceDeviceFunctionLoader = loadInstanceFunction("vkGetDeviceProcAddr");
    deviceFunctionLoader = (PFN_vkGetDeviceProcAddr) instanceDeviceFunctionLoader(device, "vkGetDeviceProcAddr");
    debug("Device function loader initialized");

    vkGetDeviceQueue(device, queueFamilyIndex, 0, &queue);
    debug("Queue retrieved");

    VkCommandPoolCreateInfo commandPoolInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .pNext = nullptr,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = queueFamilyIndex
    };

    vkCreateCommandPool(device, &commandPoolInfo, nullptr, &commandPool);
    debug("Command pool created");

    commandBuffer = allocateSingleCommandBuffer();
    debug("Command buffer allocated");

    VkFenceCreateInfo fenceInfo = {
            .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0
    };

    vkCreateFence(device, &fenceInfo, nullptr, &fence);
    debug("Fence created");
}

VkCommandBuffer allocateSingleCommandBuffer() {
    VkCommandBufferAllocateInfo commandBufferInfo = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .pNext = nullptr,
            .commandPool = commandPool,
            .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            .commandBufferCount = 1
    };

    VkCommandBuffer commandBufferHandle;
    vkAllocateCommandBuffers(device, &commandBufferInfo, &commandBufferHandle);
    return commandBufferHandle;
}

void beginSingleCommand(VkCommandBuffer commandBufferHandle) {
    VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext = nullptr,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
        .pInheritanceInfo = nullptr
    };

    vkBeginCommandBuffer(commandBufferHandle, &beginInfo);
}

void endSingleCommand(VkCommandBuffer commandBufferHandle) {
    vkEndCommandBuffer(commandBufferHandle);

    VkSubmitInfo submitInfo = {
            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .pNext = nullptr,
            .waitSemaphoreCount = 0,
            .pWaitSemaphores = nullptr,
            .pWaitDstStageMask = nullptr,
            .commandBufferCount = 1,
            .pCommandBuffers = &commandBufferHandle,
            .signalSemaphoreCount = 0,
            .pSignalSemaphores = nullptr
    };

    vkQueueSubmit(queue, 1, &submitInfo, 0);
    vkQueueWaitIdle(queue);
    vkFreeCommandBuffers(device, commandPool, 1, &commandBufferHandle);
}

void destroyDevice() {
    vkQueueWaitIdle(queue);

    vkDestroyFence(device, fence, nullptr);
    debug("Fence destroyed");

    vkDestroyCommandPool(device, commandPool, nullptr);
    debug("Command pool destroyed");

    vkDeviceWaitIdle(device);

    vkDestroyDevice(device, nullptr);
    debug("Device destroyed");
}
