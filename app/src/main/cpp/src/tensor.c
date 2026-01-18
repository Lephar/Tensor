#include "instance.h"
#include "physicalDevice.h"
#include "queue.h"
#include "device.h"
#include "memory.h"
#include "buffer.h"

JNIEXPORT void JNICALL
Java_org_arch_tensor_MainActivity_initializeTensor(JNIEnv* env, jobject this) {
    createInstance();
    selectPhysicalDevice();
    setPhysicalDeviceDetails();
    generateQueueDetails();
    createDevice();
    getQueues();

    allocateMemories();
    createBuffers();
}

JNIEXPORT void JNICALL
Java_org_arch_tensor_MainActivity_destroyTensor(JNIEnv* env, jobject this) {
    destroyBuffers();
    freeMemories();

    clearQueues();
    destroyDevice();
    destroyInstance();
}