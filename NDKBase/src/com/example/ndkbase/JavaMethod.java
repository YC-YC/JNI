package com.example.ndkbase;

import android.util.Log;

public class JavaMethod {
	private static final String TAG = "JavaMethod";
	
	private static int num = 10;	//静态数据
	private String str = "javastring";	//静态方法
	
	public static int getNum() {
		return num;
	}
	public static void setNum(int num) {
		JavaMethod.num = num;
	}
	public String getStr() {
		return str;
	}
	public void setStr(String str) {
		this.str = str;
	}
	private static void JavaStaticMethod(String str, int i)
	{
		Log.i(TAG, "我是Java本地静态方法JavaStaticMethod String=" + str + "i=" + i);
	}
	private void JavaInstancesMethod(String str, int i)
	{
		Log.i(TAG, "我是Java本地类方法JavaInstancesMethod String=" + str + "i=" + i);
	}
	
	
	
}
