LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#链接日志模块
LOCAL_LDLIBS    := -lm -llog -landroid


LOCAL_CFLASG += -pie -fPIE
LOCAL_LDFLAGS += -pie -fPIE
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include \
					$(LOCAL_PATH)/cjson \
					$(LOCAL_PATH)/uart	\
					$(LOCAL_PATH)/mySrc	\
					$(LOCAL_PATH)/pattern/mediator \
					$(LOCAL_PATH)/pattern/mememto \
					$(LOCAL_PATH)/pattern/flyweight \
					$(LOCAL_PATH)/pattern/component \
					$(LOCAL_PATH)/pattern/bridge \
					$(LOCAL_PATH)/pattern/prototype \
					$(LOCAL_PATH)/pattern/command \
					$(LOCAL_PATH)/pattern/strategy \
					$(LOCAL_PATH)/pattern/decorator \
					$(LOCAL_PATH)/pattern/proxy \
					$(LOCAL_PATH)/pattern/facade \
					$(LOCAL_PATH)/pattern/builder \
					$(LOCAL_PATH)/pattern/template \
					$(LOCAL_PATH)/pattern/adapter \
					$(LOCAL_PATH)/pattern/singleton \
					$(LOCAL_PATH)/pattern/observer	\
					$(LOCAL_PATH)/interface	\
					$(LOCAL_PATH)/ipc
					

LOCAL_MODULE    := TestBin

APP_SRCS :=  cjson/*.c \
			mySrc/*.cpp \
			pattern/singleton/*.cpp \
			pattern/observer/*.cpp \
			uart/*.cpp \
			ipc/*.cpp \
			CS75SendHelper.cpp\
			Test.cpp TestMain.cpp TestSpyFile.cpp Screencap.cpp \
			TestPattern.cpp TestStd.cpp TestInterface.cpp TestFile.cpp
			
LOCAL_SRC_FILES := $(foreach F, $(APP_SRCS), $(addprefix $(dir $(F)),$(notdir $(wildcard $(LOCAL_PATH)/$(F)))))

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

#链接日志模块
LOCAL_LDLIBS    := -lm -llog -landroid


LOCAL_CFLASG += -pie -fPIE
LOCAL_LDFLAGS += -pie -fPIE
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include \
					$(LOCAL_PATH)/ipc
					

LOCAL_MODULE    := TestBin2

APP_SRCS :=  ipc/*.cpp \
			TestMain2.cpp
			
LOCAL_SRC_FILES := $(foreach F, $(APP_SRCS), $(addprefix $(dir $(F)),$(notdir $(wildcard $(LOCAL_PATH)/$(F)))))

include $(BUILD_EXECUTABLE)

#include $(CLEAR_VARS)
#
##链接日志模块
#LOCAL_LDLIBS    := -lm -llog -landroid
#
##LOCAL_CFLASG += -pie -fPIE
##LOCAL_LDFLAGS += -pie -fPIE
#LOCAL_C_INCLUDES := $(LOCAL_PATH)/include \
#					$(LOCAL_PATH)/cjson \
#					$(LOCAL_PATH)/mySrc	
#
#LOCAL_MODULE    := TestBin
#
#APP_SRCS :=  cjson/*.c \
#			 mySrc/*.cpp \
#			CS75SendHelper.cpp\
#			Test.cpp TestMain.cpp 
#			
#LOCAL_SRC_FILES := $(foreach F, $(APP_SRCS), $(addprefix $(dir $(F)),$(notdir $(wildcard $(LOCAL_PATH)/$(F)))))
#
#include $(BUILD_SHARED_LIBRARY)
