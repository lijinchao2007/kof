LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
$(call import-add-path,$(LOCAL_PATH)/../..)
SDL_PATH := ../../SDL2
LOCAL_MODULE := kof_shared

LOCAL_C_INCLUDES := $(SDL_PATH)/include $(LOCAL_PATH)/../../src \
$(LOCAL_PATH)/../../SDL2_ttf-2.0.12 \
$(LOCAL_PATH)/../../SDL2_image-2.0.0 \
$(LOCAL_PATH)/../../SDL2_mixer-2.0.0

                
LOCAL_SRC_FILES := 	$(subst $(LOCAL_PATH)/,, \
					$(LOCAL_PATH)/$(SDL_PATH)/src/main/android/SDL_android_main.c \
					$(wildcard $(LOCAL_PATH)/../../src/*.cpp) \
					$(wildcard $(LOCAL_PATH)/../../src/cocos/*.cpp) \
					$(wildcard $(LOCAL_PATH)/../../src/shader/*.cpp) \
					$(wildcard $(LOCAL_PATH)/../../src/config/*.cpp) \
					$(wildcard $(LOCAL_PATH)/../../src/config/*.c) \
					$(wildcard $(LOCAL_PATH)/../../src/driver/*.cpp) \
					$(wildcard $(LOCAL_PATH)/../../src/driver/*.c) \
					$(wildcard $(LOCAL_PATH)/../../src/logic/*.cpp) \
					$(wildcard $(LOCAL_PATH)/../../src/tool/*.cpp) \
					$(wildcard $(LOCAL_PATH)/../../src/ui/*.cpp))

#$(warning $(LOCAL_SRC_FILES))   
   
			          


LOCAL_WHOLE_STATIC_LIBRARIES :=
LOCAL_LDLIBS+= -L$(SYSROOT)/usr/lib -L$(LOCAL_PATH)/../libs -ldl -lGLESv1_CM -lGLESv2 -llog -landroid
LOCAL_SHARED_LIBRARIES := SDL2_shared SDL2_ttf SDL2_image SDL2_mixer
LOCAL_EXPORT_CFLAGS := 

include $(BUILD_SHARED_LIBRARY)

$(call import-module,SDL2)
$(call import-module,SDL2_ttf-2.0.12)
$(call import-module,SDL2_image-2.0.0)
$(call import-module,SDL2_mixer-2.0.0)


