#include "device.h"

#include "instance.h"
#include "physicalDevice.h"
#include "queue.h"

#include "logger.h"

VkDevice device;
PFN_vkGetDeviceProcAddr deviceFunctionLoader;

void *loadDeviceFunction(const char *name) {
    void  *deviceFunction = deviceFunctionLoader(device, name);
    assert(deviceFunction);
    return deviceFunction;
}

void createDevice() {
    const char *extensions[] = {
    };

    uint32_t extensionCount = sizeof(extensions) / sizeof(const char *);

    debug("Device extensions (count = %d):", extensionCount);
    for(uint32_t index = 0; index < extensionCount; index++) {
        debug("\t%s", extensions[index]);
    }

    float *queuePriorities = malloc(queueCount * sizeof(float));

    for(uint32_t index = 0; index < queueCount; index++) {
        queuePriorities[index] = 1.0f;
    }

    queueInfos = malloc(distinctQueueFamilyCount * sizeof(VkDeviceQueueCreateInfo));

    for(uint32_t queueInfoIndex = 0; queueInfoIndex < distinctQueueFamilyCount; queueInfoIndex++) {
        queueInfos[queueInfoIndex].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfos[queueInfoIndex].pNext = nullptr;
        queueInfos[queueInfoIndex].flags = 0;
        queueInfos[queueInfoIndex].queueCount = 0,
        queueInfos[queueInfoIndex].pQueuePriorities = queuePriorities;
    }

    for(uint32_t queueIndex = 0; queueIndex < queueCount; queueIndex++) {
        VkDeviceQueueCreateInfo *queueInfo = &queueInfos[queueReferences[queueIndex]->queueInfoIndex];
        queueInfo->queueFamilyIndex = queueReferences[queueIndex]->queueFamilyIndex;

        if(queueInfo->queueCount < queueFamilyProperties[queueInfo->queueFamilyIndex].queueCount) {
            queueInfo->queueCount++;
        }
    }

    VkPhysicalDeviceVulkan11Features version11Features = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES,
        .pNext = nullptr,
    };

    VkPhysicalDeviceFeatures2 physicalDeviceFeatures2 = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
        .pNext = &version11Features,
        .features = {
        },
    };

    VkDeviceCreateInfo deviceInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = &physicalDeviceFeatures2,
        .flags = 0,
        .queueCreateInfoCount = distinctQueueFamilyCount,
        .pQueueCreateInfos = queueInfos,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount = extensionCount,
        .ppEnabledExtensionNames = extensions,
        .pEnabledFeatures = nullptr,
    };

    vkCreateDevice(physicalDevice, &deviceInfo, nullptr, &device);
    debug("Device created");
    free(queuePriorities);

    PFN_vkGetDeviceProcAddr instanceDeviceFunctionLoader = loadInstanceFunction("vkGetDeviceProcAddr");
    deviceFunctionLoader = (PFN_vkGetDeviceProcAddr) instanceDeviceFunctionLoader(device, "vkGetDeviceProcAddr");
    debug("Device function loader initialized");
}

void destroyDevice() {
    vkDeviceWaitIdle(device);
    vkDestroyDevice(device, nullptr);

    free(queueFamilyProperties);
    free(queueInfos);

    debug("Device destroyed");
}
