LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#链接日志模块
LOCAL_LDLIBS    := -lm -llog -landroid

LOCAL_CFLASG += -pie -fPIE
LOCAL_LDFLAGS += -pie -fPIE
#$(LOCAL_PATH)/include 
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include \
					$(LOCAL_PATH)/mySrc	

LOCAL_MODULE    := TestBin

APP_SRCS :=  mySrc/*.cpp \
			TestBin.cpp 
			
LOCAL_SRC_FILES := $(foreach F, $(APP_SRCS), $(addprefix $(dir $(F)),$(notdir $(wildcard $(LOCAL_PATH)/$(F)))))

include $(BUILD_EXECUTABLE)
