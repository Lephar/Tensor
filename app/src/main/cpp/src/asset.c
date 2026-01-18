#include "asset.h"

#include "logger.h"

AAssetManager *assetManager;

void initializeAssetManager(JNIEnv* env, jobject assets) {
    assetManager = AAssetManager_fromJava(env, assets);
}

size_t loadAsset(const char *filename, void **outData) {
    debug("***************************");
    AAsset *file = AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER);
    debug("%p", file);
    off_t size = AAsset_getLength(file);
    debug("***************************");

    if(*outData == nullptr) {
        *outData = malloc(size);
    }

    size_t length = AAsset_read(file, outData, size);
    assert(length == size);

    AAsset_close(file);

    return size;
}
