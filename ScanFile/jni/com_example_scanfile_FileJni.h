/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_example_scanfile_FileJni */

#ifndef _Included_com_example_scanfile_FileJni
#define _Included_com_example_scanfile_FileJni
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_example_scanfile_FileJni
 * Method:    listImpl
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_example_scanfile_FileJni_listImpl
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_example_scanfile_FileJni
 * Method:    listDirImpl
 * Signature: (Ljava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_com_example_scanfile_FileJni_listDirImpl
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_example_scanfile_FileJni
 * Method:    set
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;JJLjava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_com_example_scanfile_FileJni_set
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring, jstring, jlong, jlong, jstring, jlong);

#ifdef __cplusplus
}
#endif
#endif
