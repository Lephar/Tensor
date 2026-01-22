#pragma once

#include "tensor.h"

extern VkInstance instance;

void *loadInstanceFunction(const char *name);
void createInstance();
void destroyInstance();
