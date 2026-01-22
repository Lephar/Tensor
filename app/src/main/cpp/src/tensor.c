#include "helper.h"
#include "instance.h"
#include "device.h"
#include "pipeline.h"
#include "memory.h"

JNIEXPORT void JNICALL
Java_org_arch_tensor_MainActivity_initializeTensor(JNIEnv* env, jobject activity, jobject assets) {
    initializeAssetManager(env, assets);

    createInstance();
    selectPhysicalDevice();
    createDevice();

    createPipelineLayout();
    createShaderModules();
    createPipeline();

    allocateMemories();
    createBuffers();
}

JNIEXPORT void JNICALL
Java_org_arch_tensor_MainActivity_destroyTensor(JNIEnv* env, jobject activity) {
    destroyBuffers();
    freeMemories();

    destroyPipeline();
    destroyShaderModules();
    destroyPipelineLayout();

    destroyDevice();
    destroyInstance();
}