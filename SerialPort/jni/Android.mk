LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#链接日志模块
LOCAL_LDLIBS    := -lm -llog -landroid

LOCAL_MODULE    := SerialPort
LOCAL_SRC_FILES := SerialPort.cpp

include $(BUILD_SHARED_LIBRARY)
