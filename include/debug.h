#include <android/log.h>

#ifndef LOG_NDEBUG
#ifdef NDEBUG
#define LOG_NDEBUG 0
#else
#define LOG_NDEBUG 0
#endif
#endif


/*
 * Basic log message macros intended to emulate the behavior of log/log.h
 * in system core.  This should be dependent only on ndk exposed logging
 * functionality.
 */

#ifndef ALOG
#define ALOG(priority, tag, fmt...) \
    __android_log_print(ANDROID_##priority, tag, fmt)
#endif

#ifndef LOGV
#if LOG_NDEBUG
#define LOGV(tag, ...)   ((void)0)
#else
#define LOGV(tag, ...) ((void)ALOG(LOG_VERBOSE, tag, __VA_ARGS__))
#endif
#endif

#ifndef LOGD
#define LOGD(tag, ...) ((void)ALOG(LOG_DEBUG, tag, __VA_ARGS__))
#endif

#ifndef LOGI
#define LOGI(tag, ...) ((void)ALOG(LOG_INFO, tag, __VA_ARGS__))
#endif

#ifndef LOGW
#define LOGW(tag, ...) ((void)ALOG(LOG_WARN, tag, __VA_ARGS__))
#endif

#ifndef LOGE
#define LOGE(tag, ...) ((void)ALOG(LOG_ERROR, tag, __VA_ARGS__))
#endif

#endif
