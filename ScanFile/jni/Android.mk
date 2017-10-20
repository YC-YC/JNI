LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#打印需要添加
LOCAL_LDLIBS    := -lm -llog -landroid

LOCAL_MODULE    := ScanFile
LOCAL_SRC_FILES := ScanFile.cpp

include $(BUILD_SHARED_LIBRARY)
