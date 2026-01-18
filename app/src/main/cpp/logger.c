#include "logger.h"

void debug(const char *fmt, ...) {
    if(DEBUG) {
        va_list args;
        va_start(args, fmt);
        __android_log_vprint(ANDROID_LOG_DEBUG, TAG, fmt, args);
        va_end(args);
    }
}
