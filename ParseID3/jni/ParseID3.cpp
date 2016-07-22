#include <stddef.h>
#include <jni.h>

#include "ID3Manager.h"
#include "Debug.h"

#ifdef __cplusplus
extern "C" {
#endif

static CID3Manager g_id3Manager;

/*
 * Class:     com_zhonghong_utils_ID3Jni
 * Method:    ParseID3
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_zhonghong_utils_ID3Jni_ParseID3
  (JNIEnv *env, jclass, jstring path) {
	const char *pPath = env->GetStringUTFChars(path, NULL);
	if (pPath == NULL) {
		return false;
	}

	bool result = g_id3Manager.ParseID3(pPath);

	env->ReleaseStringUTFChars(path, pPath);

	return result;
}

/*
 * Class:     com_zhonghong_utils_ID3Jni
 * Method:    ParseID3Pic
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_zhonghong_utils_ID3Jni_ParseID3Pic__Ljava_lang_String_2Ljava_lang_String_2
  (JNIEnv *env, jclass, jstring path, jstring savePicPath) {
	const char *pPath = env->GetStringUTFChars(path, NULL);
	if (pPath == NULL) {
		return false;
	}

	const char *pSavePicPath = env->GetStringUTFChars(savePicPath, NULL);
	if (pSavePicPath == NULL) {
		env->ReleaseStringUTFChars(path, pPath);
		return false;
	}

	bool result = g_id3Manager.ParseID3Pic(pPath, pSavePicPath);

	env->ReleaseStringUTFChars(path, pPath);
	env->ReleaseStringUTFChars(savePicPath, pSavePicPath);

	return result;
}

/*
 * Class:     com_zhonghong_utils_ID3Jni
 * Method:    ParseID3Pic
 * Signature: (Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_zhonghong_utils_ID3Jni_ParseID3Pic__Ljava_lang_String_2
  (JNIEnv *env, jclass, jstring path) {
	const char *pPath = env->GetStringUTFChars(path, NULL);
	if (pPath == NULL) {
		return NULL;
	}

	jbyteArray dataArray = g_id3Manager.ParseID3Pic(pPath, env);

	env->ReleaseStringUTFChars(path, pPath);

	return dataArray;
}

/*
 * Class:     com_zhonghong_utils_ID3Jni
 * Method:    GetID3Title
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_zhonghong_utils_ID3Jni_GetID3Title
  (JNIEnv *env, jclass) {
	return env->NewStringUTF(g_id3Manager.GetTitle());
}

/*
 * Class:     com_zhonghong_utils_ID3Jni
 * Method:    GetID3Artist
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_zhonghong_utils_ID3Jni_GetID3Artist
  (JNIEnv *env, jclass) {
	return env->NewStringUTF(g_id3Manager.GetArtist());
}

/*
 * Class:     com_zhonghong_utils_ID3Jni
 * Method:    GetID3Album
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_zhonghong_utils_ID3Jni_GetID3Album
  (JNIEnv *env, jclass) {
	return env->NewStringUTF(g_id3Manager.GetAlbum());
}

#ifdef __cplusplus
}
#endif
