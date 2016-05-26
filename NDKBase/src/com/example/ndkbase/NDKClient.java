package com.example.ndkbase;

import android.util.Log;

public class NDKClient {
	static public native String HelloJni(String str1, String str2);
	
	static public native void LoadID3();
	static public native void SetFilePath(String path);
	static public native String GetID3Title();
	static public native void ReleaseID3();
	static public native void callJavaStaticMethod();	//调用Java静态方法
	static public native void callJavaInstanceMethod();	//调用Java类方法
	
	static public native void accessStaticField();	//修改Java静态变量
	static public native void accessInstanceField(JavaMethod obj);	//修改Java成员变量
	
	static public native void initIDs();	//
	static public native void nativeMethod();
	
	static public native void exceptionMethod();
	
	private static void callException()
	{
		int z = 10/0;
	}
	private static void callNormal()
	{
		Log.e("NDKBase", "callNormal");
	}
}
