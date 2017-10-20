LOCAL_PATH := $(call my-dir)

#include $(CLEAR_VARS)
#链接日志模块
#LOCAL_LDLIBS    := -lm -llog -landroid

#LOCAL_MODULE    := NDKBase
#LOCAL_SRC_FILES := NDKBase.cpp CID3.cpp dynamicLoad.cpp
#将源文件编译成共享库
#include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
#链接日志模块
LOCAL_LDLIBS    := -lm -llog -landroid
LOCAL_MODULE    := NDKBaseBIN
LOCAL_CFLASG += -pie -fPIE
LOCAL_LDFLAGS += -pie -fPIE
LOCAL_SRC_FILES := NDKBase.cpp CID3.cpp dynamicLoad.cpp
#将源文件编译成可执行文件
include $(BUILD_EXECUTABLE)
