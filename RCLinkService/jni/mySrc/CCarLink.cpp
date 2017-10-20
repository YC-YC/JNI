/*
 * CCarLink.cpp
 *
 *  Created on: 2017-9-16
 *      Author: YC2
 */
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include "CCarLink.h"
#include "CPublic.h"
#include "Log.h"

static JavaVM  *pJavaVm;
static jclass gJavaClass;
static jmethodID methodGetRadioList;
static jmethodID methodGetBtMsg;
static jmethodID methodGetCanMsg;
static jmethodID methodPutBtMsg;

int CCarLink::init(JavaVM *vm, JNIEnv *env) {
	pJavaVm = vm;
	jclass classtmp = env->FindClass("com/car/rclinkservice/jni/CarLinkJni");
	if (classtmp == NULL) {
		TestLog("init not find class");
		return 0;
	}

	gJavaClass = (jclass) env->NewGlobalRef(classtmp);
	env->DeleteLocalRef(classtmp);
	if (gJavaClass == NULL) {
		TestLog("activityClass is NULL");
		return 0;
	}

	methodGetRadioList = env->GetStaticMethodID(gJavaClass, "getRadioList",
			"()[B");
	if (methodGetRadioList == NULL) {
		TestLog("init not find method getRadioList");
		return 0;
	}
	else{
		TestLog("init find method getRadioList");
	}

	methodGetBtMsg = env->GetStaticMethodID(gJavaClass, "getBtMsg", "()[B");
	if (methodGetBtMsg == NULL) {
		printf("init not find method getBtMsg");
		return 0;
	}

	methodGetCanMsg = env->GetStaticMethodID(gJavaClass, "getCanMsg",
			"()[B");
	if (methodGetCanMsg == NULL) {
		printf("init not find method getCanMsg");
		return 0;
	}

	methodPutBtMsg = env->GetStaticMethodID(gJavaClass, "putBtMsg",
			"([B)Z");
	if (methodPutBtMsg == NULL) {
		printf("init not find method putBtMsg");
		return 0;
	}
	return 1;
}
int CCarLink::getRadioList(char* data){
	JNIEnv *myEnv = NULL;
	jsize len = 0;
	int type = CPublic::getEnv(pJavaVm, &myEnv);

	if(myEnv) {
		jbyteArray jb_array = NULL;
		jb_array = (jbyteArray)myEnv->CallStaticObjectMethod(gJavaClass, methodGetRadioList);
		if (jb_array != NULL){
			len = myEnv->GetArrayLength(jb_array);
			jbyte *jbarray = (jbyte *)malloc(len * sizeof(jbyte));
			myEnv->GetByteArrayRegion(jb_array, 0, len, jbarray);
			memcpy(data, jbarray, len);
			free(jbarray);
		}
	}

	CPublic::detachEnv(pJavaVm, type);
	return len;
}

int CCarLink::getBtMsg(char* data){
	JNIEnv *myEnv = NULL;
	jsize len = 0;
	int type = CPublic::getEnv(pJavaVm, &myEnv);

	if(myEnv) {
		jbyteArray jb_array = NULL;
		jb_array = (jbyteArray)myEnv->CallStaticObjectMethod(gJavaClass, methodGetBtMsg);
		if (jb_array != NULL){
			len = myEnv->GetArrayLength(jb_array);
			jbyte *jbarray = (jbyte *)malloc(len * sizeof(jbyte));
			myEnv->GetByteArrayRegion(jb_array, 0, len, jbarray);
			memcpy(data, jbarray, len);
			free(jbarray);
		}
	}

	CPublic::detachEnv(pJavaVm, type);
	return len;
}
int CCarLink::getCanMsg(char* data){
	JNIEnv *myEnv = NULL;
	jsize len = 0;
	int type = CPublic::getEnv(pJavaVm, &myEnv);

	if(myEnv) {
		jbyteArray jb_array = NULL;
		jb_array = (jbyteArray)myEnv->CallStaticObjectMethod(gJavaClass, methodGetCanMsg);
		if (jb_array != NULL){
			len = myEnv->GetArrayLength(jb_array);
			jbyte *jbarray = (jbyte *)malloc(len * sizeof(jbyte));
			myEnv->GetByteArrayRegion(jb_array, 0, len, jbarray);
			memcpy(data, jbarray, len);
			free(jbarray);
		}
	}

	CPublic::detachEnv(pJavaVm, type);
	return len;
}
bool CCarLink::putBtMsg(char* data, int length){
	JNIEnv *myEnv = NULL;
	jboolean result = 0;
	int type = CPublic::getEnv(pJavaVm, &myEnv);

	if(myEnv) {
		jbyteArray dataArray = myEnv->NewByteArray(length);
		myEnv->SetByteArrayRegion(dataArray, 0, length, (jbyte*)data);
		result = myEnv->CallStaticBooleanMethod(gJavaClass, methodPutBtMsg, dataArray);
	}

	CPublic::detachEnv(pJavaVm, type);
	return result;
}


