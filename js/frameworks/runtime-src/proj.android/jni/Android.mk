LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

LOCAL_SRC_FILES := ../../Classes/AppDelegate.cpp ../../Classes/ide-support/SimpleConfigParser.cpp ../../Classes/ide-support/RuntimeJsImpl.cpp hellojavascript/main.cpp ../../Classes/PluginYoutubeJS.cpp ../../Classes/PluginYoutubeJS.hpp ../../Classes/PluginYoutubeJSHelper.cpp ../../Classes/PluginYoutubeJSHelper.h ../../Classes/SDKBoxJSHelper.cpp ../../Classes/SDKBoxJSHelper.h

LOCAL_CPPFLAGS := -DSDKBOX_ENABLED
LOCAL_LDLIBS := -landroid -llog
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_WHOLE_STATIC_LIBRARIES := PluginYoutube sdkbox android_native_app_glue


LOCAL_STATIC_LIBRARIES := cocos2d_js_static

include $(BUILD_SHARED_LIBRARY)
$(call import-add-path, $(LOCAL_PATH))


$(call import-module,scripting/js-bindings/proj.android/prebuilt-mk)
$(call import-module, ./sdkbox)
$(call import-module, ./pluginyoutube)
