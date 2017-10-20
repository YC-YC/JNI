#include <android/log.h>

#define UART_DEBUG			1
#define TESTAP_DBG_USAGE	(1 << 0)
#define TESTAP_DBG_ERR		(1 << 1)
#define TESTAP_DBG_FLOW		(1 << 2)
#define TESTAP_DBG_FRAME	(1 << 3)
#define TESTAP_DBG_BW	    (1 << 4)

#ifndef LOG_TAG
#define LOG_TAG "TestJni"
#endif

#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define DebugLog(flag, msg...)  ((flag)?LOGI(msg):flag)

#define TEST_LOG 1
#define TestLog(msg...) DebugLog(TEST_LOG, msg)
