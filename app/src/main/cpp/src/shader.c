#include "shader.h"

#include "device.h"

#include "logger.h"
#include "asset.h"

VkShaderModule computeShaderModule;

VkShaderModule createShaderModule(const char *filename) {
    uint32_t *data = nullptr;
    size_t size = loadAsset(filename, (void **) &data);

    VkShaderModuleCreateInfo moduleInfo = {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .codeSize = size,
        .pCode = data
    };

    VkShaderModule shaderModule;
    vkCreateShaderModule(device, &moduleInfo, nullptr, &shaderModule);

    debug("Shader module created successfully: %s", filename);
    free(data);

    return shaderModule;
}

void createShaderModules() {
    computeShaderModule = createShaderModule("shaders/tensor.comp.spv");
    debug("Shader modules created");
}

void destroyShaderModule(VkShaderModule shaderModule) {
    vkDestroyShaderModule(device, shaderModule, nullptr);
}

void destroyShaderModules() {
    destroyShaderModule(computeShaderModule);
    debug("Shader modules destroyed");
}
