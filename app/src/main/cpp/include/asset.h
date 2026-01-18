#pragma once

#include "pch.h"

void initializeAssetManager(JNIEnv* env, jobject assets);
size_t loadAsset(const char *filename, void **outData);
