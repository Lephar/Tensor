#include "instance.h"
#include "physicalDevice.h"
#include "queue.h"
#include "device.h"

JNIEXPORT void JNICALL
Java_org_arch_tensor_MainActivity_initializeTensor(JNIEnv* env, jobject this) {
    createInstance();
    selectPhysicalDevice();
    setPhysicalDeviceDetails();
    generateQueueDetails();
    createDevice();
}

JNIEXPORT void JNICALL
Java_org_arch_tensor_MainActivity_destroyTensor(JNIEnv* env, jobject this) {
    clearQueues();
    destroyDevice();
    destroyInstance();
}