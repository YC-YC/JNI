LOCAL_PATH := $(call my-dir)

#加入第三方库
include $(CLEAR_VARS)  
LOCAL_MODULE := Hello    
LOCAL_SRC_FILES := carlib/libHello.so          
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/carlib/include
include $(PREBUILT_SHARED_LIBRARY) 

include $(CLEAR_VARS)

LOCAL_LDLIBS    := -lm -llog -landroid
#LOCAL_CFLASG += -pie -fPIE
#LOCAL_LDFLAGS += -pie -fPIE

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include \
					$(LOCAL_PATH)/mySrc	

LOCAL_MODULE    := LinkService

APP_SRCS :=  mySrc/*.cpp \
			LinkService.cpp 
			
LOCAL_SRC_FILES := $(foreach F, $(APP_SRCS), $(addprefix $(dir $(F)),$(notdir $(wildcard $(LOCAL_PATH)/$(F)))))
		

#加入第三方库
LOCAL_SHARED_LIBRARIES := libHello


include $(BUILD_SHARED_LIBRARY)
