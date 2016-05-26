LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
#链接日志模块
LOCAL_LDLIBS    := -lm -llog -landroid

LOCAL_MODULE    := NDKBase
LOCAL_SRC_FILES := NDKBase.cpp CID3.cpp dynamicLoad.cpp

#将源文件编译成共享库
include $(BUILD_SHARED_LIBRARY)
