#include <android/log.h>
#include <jni.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include "ScopedUtfChars.h"
#include "com_example_scanfile_FileJni.h"

#define LOG_TAG "ScanFile"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

JNIEXPORT void JNICALL Java_com_example_scanfile_FileJni_listImpl
  (JNIEnv* env, jclass, jstring javaPath){

	 LOGI("enter --\r\n");
	ScopedUtfChars path(env, javaPath);
	    if (path.c_str() == NULL) {
	        return;
	    }
	    DIR *dp;
	    struct dirent *entry;
	    struct stat buff;
	    LOGI("opendir --\r\n");
	    dp = opendir(path.c_str());
	    LOGI("opendir ++\r\n");
	    if (dp != NULL){
	    	while((entry = readdir(dp)) != NULL){
//	    		LOGI("get file = [%s]\r\n", entry->d_name);
	    	}
	    	closedir(dp);
	    }
	    LOGI("enter ++\r\n");
	    return;
}
