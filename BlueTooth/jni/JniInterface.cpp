#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "comdef.h"
#include "debug.h"
#include "CBlueTooth.h"

/*
 * Jni方法采用动态加载方法
 *
 */
static JNIEnv * gEnv = NULL;
static JavaVM* g_Jvm = NULL;
static jclass g_cls_BlueToothActivity = NULL;
static CBlueTooth* pBlueTooth = NULL;

bool JNI_CallJavaIntStringStringMethod
(JNIEnv * env, const char* function, int arg1, const char* arg2, char* result, int resultLen)
{
	jclass clazz = NULL;
	jobject jobj = NULL;
	jmethodID construct_method;
	jmethodID instanse_method;


	//查找Class对象
	clazz = env->FindClass("com.zhonghong.jni.JniClient");
	if (clazz == NULL)
	{
		TestAp_Printf(UART_DEBUG, "FindClass com.example.ndkbase.JavaMethod error");
		return false;
	}

	//查找默认构造函数
	construct_method = gEnv->GetMethodID(clazz, "<init>", "()V");
	if (construct_method == NULL)
	{
		TestAp_Printf(UART_DEBUG, "Find default construct method error");
		return false;
	}

	instanse_method = gEnv->GetMethodID(clazz, function, "(ILjava/lang/String;)Ljava/lang/String;");
	if (instanse_method == NULL)
	{
		TestAp_Printf(UART_DEBUG, "Find instanse_method error");
		return false;
	}

	//创建类的实例
	jobj = gEnv->NewObject(clazz, construct_method);
	if (jobj == NULL)
	{
		TestAp_Printf(UART_DEBUG, "NewObject error");
		return false;
	}

	//调用实例方法
	jstring str = gEnv->NewStringUTF(arg2);
	jstring strRet = (jstring)gEnv->CallObjectMethod(jobj, instanse_method, arg1, str);

	const char* newStr = gEnv->GetStringUTFChars(strRet, NULL);
	strncpy(result, newStr, resultLen-1);
	gEnv->ReleaseStringUTFChars(strRet, newStr);
	gEnv->DeleteLocalRef(strRet);
	//回收本地资源
	gEnv->DeleteLocalRef(clazz);
	gEnv->DeleteLocalRef(jobj);
	gEnv->DeleteLocalRef(str);
	return true;
}

bool JNI_CallJavaStaticIntStringStringMethod
(JNIEnv * env, const char* function, int arg1, const char* arg2, char* result, int resultLen)
{

//	jclass clazz = NULL;
		jmethodID static_method;

//		//查找Class对象
//		clazz = env->FindClass("com.zhonghong.jni.JniClient");
//		if (clazz == NULL)
//		{
//			TestAp_Printf(UART_DEBUG, "com.zhonghong.jni.JniClient error");
//			return false;
//		}

		//查找static 方法
//		static_method = env->GetStaticMethodID(clazz, function, "(ILjava/lang/String;)Ljava/lang/String;");
		static_method = env->GetStaticMethodID(g_cls_BlueToothActivity, function, "(ILjava/lang/String;)Ljava/lang/String;");
		if (static_method == NULL)
		{
			TestAp_Printf(UART_DEBUG, "GetStaticMethodID JavaStaticMethod error");
			return false;
		}

		jstring str = env->NewStringUTF(arg2);
		//调用Java方法
		jstring strRet = (jstring)env->CallStaticObjectMethod(g_cls_BlueToothActivity, static_method, arg1, str);
		const char* newStr = env->GetStringUTFChars(strRet, NULL);
			strncpy(result, newStr, resultLen-1);
			env->ReleaseStringUTFChars(strRet, newStr);
			env->DeleteLocalRef(strRet);

		//删除本地资源
//		env->DeleteLocalRef(clazz);
		env->DeleteLocalRef(str);
		return true;
}
const char* CJavaForString(int cmd, const char*val)
{
	if (g_Jvm == NULL)
	{
		LOGI("CJavaForString VM null\r\n");
		return NULL;
	}
	bool bAttackek = false;
	JNIEnv * env = NULL;
	int state = g_Jvm->GetEnv((void**)&env, JNI_VERSION_1_6) ;
	if (state < 0)
	{
		state = g_Jvm->AttachCurrentThread(&env, NULL);
		TestAp_Printf(UART_DEBUG, "AttachCurrentThread\r\n");
		if (state < 0)
		{
			TestAp_Printf(UART_DEBUG, "AttachCurrentThread Err\r\n");
			return NULL;
		}
		bAttackek = true;
	}
	static char ret[MAX_PATH] = {0};
	ZeroMemory(ret, MAX_PATH);

	JNI_CallJavaStaticIntStringStringMethod(env, "CCallJavaForString", cmd, val,ret, MAX_PATH);

	if (bAttackek)
	{
		g_Jvm->DetachCurrentThread();
	}
	return ret;
}

void HelloBlueTooth(JNIEnv *, jclass)
{

}

jstring GetBlueToothVersion(JNIEnv *env, jclass clz)
{
	const char* pRet = CJavaForString(100, "I am from C!");
	if (pRet != NULL)
	{
		LOGI("Native CJavaForString ret=[%s]\r\n", pRet);
	}
//	for (int i = 0; i < 100; i++)
//	{
//		CJavaForString(100, "I am from C thread!");
//	}
	return env->NewStringUTF(pBlueTooth->GetBlueToothVersion());
}

/*
 * 方法对应表
 * {Java方法，方法签名(参数+返回值)，本地对应方法}
 */
const JNINativeMethod g_methods[] = {
		{"HelloBlueTooth", "()V", (void*)HelloBlueTooth},
		{"GetBlueToothVersion", "()Ljava/lang/String;", (void*)GetBlueToothVersion}
};


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
	g_Jvm = vm;
	gEnv = env;
	cls = env->FindClass("com/zhonghong/jni/JniClient");
	if (cls == NULL)
	{
		TestAp_Printf(UART_DEBUG, "FindClass Err\r\n");
		return JNI_ERR;
	}

	//生成全局弱引用
	g_cls_BlueToothActivity = (jclass)env->NewWeakGlobalRef(cls);

	env->DeleteLocalRef(cls);


	//注册JNI方法
	env->RegisterNatives(g_cls_BlueToothActivity, g_methods, sizeof(g_methods)/sizeof(g_methods[0]));
	pBlueTooth = new CBlueTooth();
	TestAp_Printf(UART_DEBUG, "OnLoad Success\r\n");
	return JNI_VERSION_1_6;
}

//卸载so时回调
JNIEXPORT void /*JNICALL*/ JNI_ONUnLoad(JavaVM* vm, void* reserved)
 {
	JNIEnv * env = NULL;
	jclass cls = NULL;
	if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK) {
		TestAp_Printf(UART_DEBUG, "JNI_ONUnLoad GetEnv Err\r\n");
		return;
	}
	env->UnregisterNatives(g_cls_BlueToothActivity);
	env->DeleteWeakGlobalRef(g_cls_BlueToothActivity);
	if (NULL != pBlueTooth)
	{
		delete pBlueTooth;
		pBlueTooth = NULL;
	}
}
