#include "shader.h"

#include "device.h"

#include "logger.h"
#include "asset.h"

VkShaderModule shaderModule;

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

    VkShaderModule module;
    vkCreateShaderModule(device, &moduleInfo, nullptr, &module);

    debug("Shader module created successfully: %s", filename);
    free(data);

    return module;
}

void createShaderModules() {
    shaderModule = createShaderModule("shaders/tensor.comp.spv");
    debug("Shader modules created");
}

void destroyShaderModule(VkShaderModule module) {
    vkDestroyShaderModule(device, module, nullptr);
}

void destroyShaderModules() {
    destroyShaderModule(shaderModule);
    debug("Shader modules destroyed");
}
