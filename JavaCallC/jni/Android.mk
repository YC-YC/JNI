LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#打印需要添加
LOCAL_LDLIBS    := -lm -llog -landroid

LOCAL_MODULE    := JavaCallC
LOCAL_SRC_FILES := JavaCallC.cpp

include $(BUILD_SHARED_LIBRARY)
