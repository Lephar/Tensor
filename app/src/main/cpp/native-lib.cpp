#include <string>

extern "C" {
#include "instance.h"
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_arch_tensor_MainActivity_initializeTensor(JNIEnv* env, jobject) {
    createInstance();
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C" JNIEXPORT void JNICALL
Java_org_arch_tensor_MainActivity_destroyTensor(JNIEnv* env, jobject) {
    destroyInstance();
}