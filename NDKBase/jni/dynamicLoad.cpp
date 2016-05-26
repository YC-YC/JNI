/*
 * dynamicLoad.cpp
 *
 *  Created on: 2016-1-11
 *      Author: YC
 */

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

#ifdef __cplusplus
extern "C" {
#endif

static JNIEnv * gEnv = NULL;
static void callJava()
{
	jclass clazz = NULL;
		jobject jobj = NULL;
		jmethodID construct_method;
		jmethodID instanse_method;

		//查找Class对象
		clazz = gEnv->FindClass("com.example.ndkbase.JavaMethod");
		if (clazz == NULL)
		{
			TestAp_Printf(UART_DEBUG, "FindClass com.example.ndkbase.JavaMethod error");
			return;
		}

		//查找默认构造函数
		construct_method = gEnv->GetMethodID(clazz, "<init>", "()V");
		if (construct_method == NULL)
		{
			TestAp_Printf(UART_DEBUG, "Find default construct method error");
			return;
		}

		instanse_method = gEnv->GetMethodID(clazz, "JavaInstancesMethod", "(Ljava/lang/String;I)V");
		if (instanse_method == NULL)
		{
			TestAp_Printf(UART_DEBUG, "Find instanse_method error");
			return;
		}

		//创建类的实例
		jobj = gEnv->NewObject(clazz, construct_method);
		if (jobj == NULL)
		{
			TestAp_Printf(UART_DEBUG, "NewObject error");
			return;
		}

		//调用实例方法
		jstring arg = gEnv->NewStringUTF("Java传入的参数");
		gEnv->CallVoidMethod(jobj, instanse_method, arg, 50);

		//回收本地资源
		gEnv->DeleteLocalRef(clazz);
		gEnv->DeleteLocalRef(jobj);
		gEnv->DeleteLocalRef(arg);
}

jobjectArray nativeGetStrings(JNIEnv* env, jobject obj, jint count, jstring sample)
{
	jobjectArray str_arr = NULL;
	jclass cls_string = NULL;
	jmethodID init_method = NULL;
	jobject obj_str = NULL;
	const char* c_str = NULL;

	char buff[256] = {0};

	if (env->EnsureLocalCapacity(3) != JNI_OK)
	{
		TestAp_Printf(UART_DEBUG, "EnsureLocalCapacity(3) Err\r\n");
		return NULL;
	}

	c_str = env->GetStringUTFChars(sample, NULL);
	if (c_str == NULL)
	{
		TestAp_Printf(UART_DEBUG, "GetStringUTFChars Err\r\n");
		return NULL;
	}

	cls_string = env->FindClass("java/lang/String");
	if (cls_string == NULL)
	{
		return NULL;
	}

	init_method = env->GetMethodID(cls_string, "<init>", "()V");
	if (init_method == NULL)
	{
		return NULL;
	}

	obj_str = env->NewObject(cls_string, init_method);
	if (obj_str == NULL)
	{
		env->DeleteLocalRef(cls_string);
		return NULL;
	}

	str_arr = env->NewObjectArray(count, cls_string, obj_str);
	if (str_arr == NULL)
	{
		env->DeleteLocalRef(cls_string);
		env->DeleteLocalRef(obj_str);
		return NULL;
	}

	for(int i = 0; i < count; i++)
	{
		memset(buff, 0, sizeof(buff));
		sprintf(buff, c_str, i);
		jstring newString = env->NewStringUTF(buff);
		env->SetObjectArrayElement(str_arr, i, newString);
		env->DeleteLocalRef(newString);	//为避免局部引用表溢出，必需要清除数据
	}


	env->ReleaseStringUTFChars(sample, c_str);

	env->DeleteLocalRef(obj_str);
	env->DeleteLocalRef(cls_string);
	callJava();
	return str_arr;
}


/*
 * 方法对应表
 */
const JNINativeMethod g_methods[] = {
		{"getStrings", "(ILjava/lang/String;)[Ljava/lang/String;", (void*)nativeGetStrings}
};

static jclass g_cls_MainActivity = NULL;

//加载so时回调
JNIEXPORT jint /*JNICALL*/ JNI_OnLoad(JavaVM* vm, void* reserved)
{
	TestAp_Printf(UART_DEBUG, "OnLoad Start\r\n");
	JNIEnv * env = NULL;
	jclass cls = NULL;
	if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK)
	{
		TestAp_Printf(UART_DEBUG, "OnLoad GetEnv Err\r\n");
		return JNI_ERR;
	}
	gEnv = env;
	cls = env->FindClass("com.example.ndkbase.MainActivity");
	if (cls == NULL)
	{
		TestAp_Printf(UART_DEBUG, "FindClass Err\r\n");
		return JNI_ERR;
	}

	//生成全局弱引用
	g_cls_MainActivity = (jclass)env->NewWeakGlobalRef(cls);

	env->DeleteLocalRef(cls);


	//注册JNI方法
	env->RegisterNatives(g_cls_MainActivity, g_methods, sizeof(g_methods)/sizeof(g_methods[0]));
	TestAp_Printf(UART_DEBUG, "OnLoad End\r\n");

	TestAp_Printf(UART_DEBUG, "OnLoad callJava End\r\n");
	return JNI_VERSION_1_6;
}

//卸载so时回调
JNIEXPORT void /*JNICALL*/ JNI_ONUnLoad(JavaVM* vm, void* reserved)
 {
	gEnv = NULL;
	JNIEnv * env = NULL;
	jclass cls = NULL;
	if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK) {
		TestAp_Printf(UART_DEBUG, "JNI_ONUnLoad GetEnv Err\r\n");
		return;
	}

	env->UnregisterNatives(g_cls_MainActivity);
	env->DeleteWeakGlobalRef(g_cls_MainActivity);
}

#ifdef __cplusplus
}
#endif


