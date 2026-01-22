#include "helper.h"

AAssetManager *assetManager;

void debug(const char *fmt, ...) {
    if(DEBUG) {
        va_list args;
        va_start(args, fmt);
        __android_log_vprint(ANDROID_LOG_DEBUG, TAG, fmt, args);
        va_end(args);
    }
}

// NOTICE: These min/max macros are for internal use only.
// Separate functions prevent double-evaluation and guarantee type-safety.

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

// END OF NOTICE

uint64_t align(uint64_t value, uint64_t alignment) {
    return (value + alignment - 1) / alignment * alignment;
}

uint64_t alignBack(uint64_t value, uint64_t alignment) {
    return value / alignment * alignment;
}

float radians(float degrees) {
    return M_PI * degrees / 180.0f;
}

int32_t compareFloat(float first, float second) {
    float difference = first - second;

    return (difference > EPSILON) - (difference < -EPSILON);
}

int8_t bmin(int8_t first, int8_t second) {
    return min(first, second);
}

int8_t bmax(int8_t first, int8_t second) {
    return max(first, second);
}

uint8_t ubmin(uint8_t first, uint8_t second) {
    return min(first, second);
}

uint8_t ubmax(uint8_t first, uint8_t second) {
    return max(first, second);
}

int16_t smin(int16_t first, int16_t second) {
    return min(first, second);
}

int16_t smax(int16_t first, int16_t second) {
    return max(first, second);
}

uint16_t usmin(uint16_t first, uint16_t second) {
    return min(first, second);
}

uint16_t usmax(uint16_t first, uint16_t second) {
    return max(first, second);
}

int32_t imin(int32_t first, int32_t second) {
    return min(first, second);
}

int32_t imax(int32_t first, int32_t second) {
    return max(first, second);
}

uint32_t umin(uint32_t first, uint32_t second) {
    return min(first, second);
}

uint32_t umax(uint32_t first, uint32_t second) {
    return max(first, second);
}

int64_t lmin(int64_t first, int64_t second) {
    return min(first, second);
}

int64_t lmax(int64_t first, int64_t second) {
    return max(first, second);
}

uint64_t ulmin(uint64_t first, uint64_t second) {
    return min(first, second);
}

uint64_t ulmax(uint64_t first, uint64_t second) {
    return max(first, second);
}

void initializeAssetManager(JNIEnv* env, jobject assets) {
    assetManager = AAssetManager_fromJava(env, assets);
}

size_t loadAsset(const char *filename, void **outData) {
    AAsset *file = AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER);
    off_t size = AAsset_getLength(file);

    if(*outData == nullptr) {
        *outData = malloc(size);
    }

    size_t length = AAsset_read(file, *outData, size);
    assert(length == size);

    AAsset_close(file);

    return size;
}
