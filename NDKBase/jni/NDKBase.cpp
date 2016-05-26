#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "com_example_ndkbase_NDKClient.h"
#include "CID3.h"
#include <time.h>

static CID3* pID3 =NULL;
static CID3 ID3;

JNIEXPORT jstring JNICALL Java_com_example_ndkbase_NDKClient_HelloJni
  (JNIEnv *env, jclass art, jstring str1, jstring str2)
{
	TestAp_Printf(TESTAP_DBG_ERR, "jni HelloJni\r\n");
	jstring str = env->NewStringUTF("Hello jni!");
	return str;
}

/*
 * Class:     com_example_ndkbase_NDKClient
 * Method:    LoadID3
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ndkbase_NDKClient_LoadID3
  (JNIEnv *, jclass)
{
	if (NULL ==pID3){
		pID3 = new CID3();
	}
}

/*
 * Class:     com_example_ndkbase_NDKClient
 * Method:    SetFilePath
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_example_ndkbase_NDKClient_SetFilePath
  (JNIEnv *env, jclass, jstring path)
{
	char buf[128] = {0};
	const char* pGet = env->GetStringUTFChars(path, NULL);
	if (pGet == NULL)
	{
		return;
	}
	sprintf(buf, "%s", pGet);
	TestAp_Printf(UART_DEBUG, "GetSetFilePath = [%s]\r\n", buf);
	env->ReleaseStringUTFChars(path, pGet);
	if (pID3 != NULL)
	{
		TestAp_Printf(UART_DEBUG, "pID3->SetFilePath\r\n");
		pID3->SetFilePath(buf);
	}
	ID3.SetFilePath(buf);

}

/*
 * Class:     com_example_ndkbase_NDKClient
 * Method:    GetID3Title
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_ndkbase_NDKClient_GetID3Title
  (JNIEnv *env, jclass)
{

	struct tm tmp;
	tmp.tm_year = 2015 - 1900;
	tmp.tm_mon = 0;
	tmp.tm_mday = 1;
	tmp.tm_hour = 0;
	tmp.tm_min = 15;
	tmp.tm_sec = 0;
//	tmp.tm_year = 1970 - 1900;
//	tmp.tm_mon = 0;
//	tmp.tm_mday = 1;
//	tmp.tm_hour = 0;
//	tmp.tm_min = 0;
//	tmp.tm_sec = 0;
	tmp.tm_wday = 0;
	tmp.tm_yday = 0;
	tmp.tm_isdst = 0;


	time_t seconds = mktime(&tmp);
	TestAp_Printf(UART_DEBUG, "Jni Gettime = %d",seconds);
	TestAp_Printf(UART_DEBUG, "Jni Gettime = %s",ctime(&seconds));
	time_t current = time(NULL);
	TestAp_Printf(UART_DEBUG, "Jni Curtime = %d",current);
	TestAp_Printf(UART_DEBUG, "Jni Curtime = %s",ctime(&current));
	if (pID3 != NULL)
	{
		TestAp_Printf(UART_DEBUG, "Jni GetID3Title = %s",pID3->GetTitle());
		return env->NewStringUTF(pID3->GetTitle());
	}
	return NULL;
}

/*
 * Class:     com_example_ndkbase_NDKClient
 * Method:    ReleaseID3
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ndkbase_NDKClient_ReleaseID3
  (JNIEnv *, jclass)
{
	if (pID3 != NULL)
	{
		delete pID3;
		pID3 = NULL;
	}
}

/*
 * Class:     com_example_ndkbase_NDKClient
 * Method:    callJavaStaticMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ndkbase_NDKClient_callJavaStaticMethod
  (JNIEnv *env, jclass)
{
	jclass clazz = NULL;
	jmethodID static_method;

	//查找Class对象
	clazz = env->FindClass("com.example.ndkbase.JavaMethod");
	if (clazz == NULL)
	{
		TestAp_Printf(UART_DEBUG, "FindClass com.example.ndkbase.JavaMethod error");
		return;
	}

	//查找static 方法
	static_method = env->GetStaticMethodID(clazz, "JavaStaticMethod", "(Ljava/lang/String;I)V");
	if (static_method == NULL)
	{
		TestAp_Printf(UART_DEBUG, "GetStaticMethodID JavaStaticMethod error");
		return;
	}

	jstring arg = env->NewStringUTF("Java传入的参数");
	//调用Java方法
	env->CallStaticVoidMethod(clazz, static_method, arg, 100);

	//删除本地资源
	env->DeleteLocalRef(clazz);
	env->DeleteLocalRef(arg);
}

/*
 * Class:     com_example_ndkbase_NDKClient
 * Method:    callJavaInstaceMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ndkbase_NDKClient_callJavaInstanceMethod
  (JNIEnv *env, jclass)
{
	jclass clazz = NULL;
	jobject jobj = NULL;
	jmethodID construct_method;
	jmethodID instanse_method;

	//查找Class对象
	clazz = env->FindClass("com.example.ndkbase.JavaMethod");
	if (clazz == NULL)
	{
		TestAp_Printf(UART_DEBUG, "FindClass com.example.ndkbase.JavaMethod error");
		return;
	}

	//查找默认构造函数
	construct_method = env->GetMethodID(clazz, "<init>", "()V");
	if (construct_method == NULL)
	{
		TestAp_Printf(UART_DEBUG, "Find default construct method error");
		return;
	}

	instanse_method = env->GetMethodID(clazz, "JavaInstancesMethod", "(Ljava/lang/String;I)V");
	if (instanse_method == NULL)
	{
		TestAp_Printf(UART_DEBUG, "Find instanse_method error");
		return;
	}

	//创建类的实例
	jobj = env->NewObject(clazz, construct_method);
	if (jobj == NULL)
	{
		TestAp_Printf(UART_DEBUG, "NewObject error");
		return;
	}

	//调用实例方法
	jstring arg = env->NewStringUTF("Java传入的参数");
	env->CallVoidMethod(jobj, instanse_method, arg, 50);

	//回收本地资源
	env->DeleteLocalRef(clazz);
	env->DeleteLocalRef(jobj);
	env->DeleteLocalRef(arg);
}

/*
 * Class:     com_example_ndkbase_NDKClient
 * Method:    accessStaticField
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ndkbase_NDKClient_accessStaticField
  (JNIEnv *env, jclass)
{
	jclass clazz = NULL;
	jfieldID fid = NULL;
	jint num ;

	clazz = env->FindClass("com.example.ndkbase.JavaMethod");
	if (clazz == NULL)
	{
		TestAp_Printf(UART_DEBUG, "FindClass Error\r\n");
		return;
	}

	//获取变量
	fid = env->GetStaticFieldID(clazz, "num", "I");
	if (fid == NULL)
	{
		TestAp_Printf(UART_DEBUG, "GetStaticFieldID Error\r\n");
		return;
	}

	//获取变量的值
	num = env->GetStaticIntField(clazz, fid);

	//修改变量值
	env->SetStaticIntField(clazz, fid, 100);

	env->DeleteLocalRef(clazz);
}

/*
 * Class:     com_example_ndkbase_NDKClient
 * Method:    accessInstanceField
 * Signature: (Lcom/example/ndkbase/JavaMethod;)V
 */
JNIEXPORT void JNICALL Java_com_example_ndkbase_NDKClient_accessInstanceField
  (JNIEnv *env, jclass, jobject obj)
{
	jclass clazz = NULL;
	jfieldID fid = NULL;
	jstring j_str = NULL;
	jstring j_newstr = NULL;


	//获取类的实例引用
	clazz = env->GetObjectClass(obj);
	if (clazz == NULL)
	{
		TestAp_Printf(UART_DEBUG, "GetObjectClass Error\r\n");
		return;
	}

	//查找ID
	fid = env->GetFieldID(clazz, "str", "Ljava/lang/String;");
	if (fid == NULL)
	{
		TestAp_Printf(UART_DEBUG, "GetFieldID Error\r\n");
		return;
	}

	//查找变量
	j_str = (jstring)env->GetObjectField(obj, fid);
	if (j_str == NULL)
	{
		TestAp_Printf(UART_DEBUG, "GetFieldID Error\r\n");
				return;
	}

	j_newstr = env->NewStringUTF("C++ newString");
	if (j_newstr == NULL)
	{
		TestAp_Printf(UART_DEBUG, "NewStringUTF error\r\n");
		return;
	}

	//设置成员变量
	env->SetObjectField(obj, fid, j_newstr);

	env->DeleteLocalRef(clazz);
	env->DeleteLocalRef(j_str);
	env->DeleteLocalRef(j_newstr);
}

/*
 * Class:     com_example_ndkbase_NDKClient
 * Method:    exceptionMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ndkbase_NDKClient_exceptionMethod
  (JNIEnv *env , jclass clz)
{
	jclass clazz = NULL;
	jmethodID static_method = NULL;


	//查找static 方法
	static_method = env->GetStaticMethodID(clz, "callException", "()V");
	if (static_method != NULL)
	{
		env->CallStaticVoidMethod(clz, static_method);
	}

	/*
	 * 异常处理方式一
	 */
/*	if (env->ExceptionCheck())
	{
		env->ExceptionDescribe();	//打印这个异常的堆栈信息
		env->ExceptionClear();	//清除异常堆栈信息的缓冲区（如果不清除，后面调用ThrowNew抛出的异常堆栈信息会覆盖前面的异常信息）
		env->ThrowNew(env->FindClass("java/lang/Exception"), "JNI抛出的异常");
	}*/

	/*
	 * 异常处理方式二
	 */
	jthrowable exc = NULL;
	exc = env->ExceptionOccurred();//返回指向当前异常的引用
	if (exc != NULL)
	{
		env->ExceptionDescribe();
		env->ExceptionClear();
		env->ThrowNew(env->FindClass("java/lang/Exception"), "JNI抛出的异常");
	}

	static_method = env->GetStaticMethodID(clz, "callNormal", "()V");
	if (static_method != NULL)
	{
		env->CallStaticVoidMethod(clz, static_method);
	}
}
