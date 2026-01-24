#include "helper.h"
#include "instance.h"
#include "device.h"
#include "memory.h"
#include "pipeline.h"
#include "dispatch.h"

JNIEXPORT void JNICALL
Java_org_arch_tensor_MainActivity_initializeTensor(JNIEnv* env, jobject activity, jobject assets) {
    initializeAssetManager(env, assets);

    createInstance();
    selectPhysicalDevice();
    createDevice();

    allocateMemories();
    createBuffers();

    createShaderModules();
    createDescriptorSet();
    createPipeline();
}

JNIEXPORT void JNICALL
Java_org_arch_tensor_MainActivity_runTensor(JNIEnv* env, jobject activity, jstring string) {
    const char *message = (*env)->GetStringUTFChars(env, string, nullptr);
    debug("Message: %s", message);

    recordCommands();
    dispatch();
    waitDispatch();

    (*env)->ReleaseStringUTFChars(env, string, message);
}

JNIEXPORT void JNICALL
Java_org_arch_tensor_MainActivity_destroyTensor(JNIEnv* env, jobject activity) {
    destroyPipeline();
    destroyDescriptorSet();
    destroyShaderModules();

    destroyBuffers();
    freeMemories();

    destroyDevice();
    destroyInstance();
}
