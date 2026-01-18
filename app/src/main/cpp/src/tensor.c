#include "asset.h"
#include "instance.h"
#include "physicalDevice.h"
#include "queue.h"
#include "device.h"
#include "shader.h"
#include "memory.h"
#include "buffer.h"

JNIEXPORT void JNICALL
Java_org_arch_tensor_MainActivity_initializeTensor(JNIEnv* env, jobject activity, jobject assets) {
    initializeAssetManager(env, assets);

    createInstance();
    selectPhysicalDevice();
    setPhysicalDeviceDetails();
    generateQueueDetails();
    createDevice();
    getQueues();

    createShaderModules();

    allocateMemories();
    createBuffers();
}

JNIEXPORT void JNICALL
Java_org_arch_tensor_MainActivity_destroyTensor(JNIEnv* env, jobject jobj) {
    destroyBuffers();
    freeMemories();

    destroyShaderModules();

    clearQueues();
    destroyDevice();
    destroyInstance();
}