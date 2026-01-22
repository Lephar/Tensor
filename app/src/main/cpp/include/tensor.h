#pragma once

#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <syslog.h>
#include <limits.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/sysinfo.h>

#include <jni.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_android.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>

#ifndef NDEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

#if __STDC_VERSION__ < 202311L
#define nullptr NULL
#endif

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#define TAG "Tensor"
