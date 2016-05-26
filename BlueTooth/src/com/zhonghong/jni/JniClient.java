package com.zhonghong.jni;

import android.util.Log;

/*
 * Jni½»»¥º¯Êý
 */
public class JniClient {
	
	
	private static final String TAG = "JniClient";
	
	static public native void HelloBlueTooth();	//²âÊÔº¯Êý
	static public native String GetBlueToothVersion();	//
	
	public static String CCallJavaForString(int cmd, String val)
	{
		Log.i(TAG, "CCallJavaForString cmd=" + cmd + ", val=" + val);
		return "Java CCallJavaForString";
	}
	
	private void LOG(String str)
	{
		Log.i(TAG, str);
	}
}
