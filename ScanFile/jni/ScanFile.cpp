#include <android/log.h>
#include <jni.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include "ScopedUtfChars.h"
#include "toStringArray.h"
#include "JniConstants.h"
#include "ScopedReaddir.h"
#include "com_example_scanfile_FileJni.h"
#include <string>
#include <vector>

#define LOG_TAG "ScanFile"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

typedef std::vector<std::string> DirEntries;

static bool readDirectory(JNIEnv* env, jstring javaPath, DirEntries& entries) {
    ScopedUtfChars path(env, javaPath);
    if (path.c_str() == NULL) {
        return false;
    }

    ScopedReaddir dir(path.c_str());
    const char* filename;
    while ((filename = dir.next()) != NULL) {
        if (strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0) {
            // TODO: this hides allocation failures from us. Push directory iteration up into Java?
            entries.push_back(filename);
        }
    }
    return !dir.isBad();
}

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
	    		entry->d_type == DT_DIR;
//	    		LOGI("get file = [%s]\r\n", entry->d_name);
	    	}
	    	closedir(dp);
	    }
	    LOGI("enter ++\r\n");
	    return;
}

JNIEXPORT jobjectArray JNICALL Java_com_example_scanfile_FileJni_listDirImpl
  (JNIEnv *env, jclass, jstring javaPath){
	DirEntries entries;
	if (!readDirectory(env, javaPath, entries)) {
		return NULL;
	}
	// Translate the intermediate form into a Java String[].
	return toStringArray(env, entries);
}


JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	LOGI("OnLoad Start\r\n");
	JNIEnv * env = NULL;
	jclass cls = NULL;
	if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK)
	{
		LOGI("OnLoad GetEnv Err\r\n");
		return JNI_ERR;
	}
	JniConstants::init(env);
	return JNI_VERSION_1_6;
}
