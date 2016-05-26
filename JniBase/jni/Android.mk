LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := JniBase
LOCAL_SRC_FILES := JniBase.cpp

include $(BUILD_SHARED_LIBRARY)
