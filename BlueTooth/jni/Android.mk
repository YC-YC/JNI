LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#������־ģ��
LOCAL_LDLIBS    := -lm -llog -landroid

LOCAL_MODULE    := BlueTooth

LOCAL_C_INCLUDES	:= F:\zhonghong\include

LOCAL_SRC_FILES := JniInterface.cpp CBlueTooth.cpp CUartCtrl.cpp UartCom.cpp

include $(BUILD_SHARED_LIBRARY)
