/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_yc_javacallc_Connection */

#ifndef _Included_com_yc_javacallc_Connection
#define _Included_com_yc_javacallc_Connection
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_yc_javacallc_Connection
 * Method:    open
 * Signature: (Ljava/lang/String;I)Ljava/io/FileDescriptor;
 */
JNIEXPORT jobject JNICALL Java_com_yc_javacallc_Connection_open
  (JNIEnv *, jclass, jstring, jint);

/*
 * Class:     com_yc_javacallc_Connection
 * Method:    close
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_yc_javacallc_Connection_close
  (JNIEnv *, jclass);

/*
 * Class:     com_yc_javacallc_Connection
 * Method:    IOCtl
 * Signature: (Ljava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_com_yc_javacallc_Connection_IOCtl
  (JNIEnv *, jclass, jstring, jint, jint);

#ifdef __cplusplus
}
#endif
#endif
