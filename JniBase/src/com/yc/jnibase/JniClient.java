/**
 * 
 */
package com.yc.jnibase;

/**
 * @author YC
 * @time 2016-5-26 下午2:32:38
 */
public class JniClient {

	
	public static String CCallJavaForString(int cmd, String val){
		return JniManager.getInstanse().CCallJavaForString(cmd, val);
	}
	
	public static boolean CCallJavaForInt(int cmd, int val){
		return JniManager.getInstanse().CCallJavaForInt(cmd, val);
	}
	
	public static native void JavaCallCForString(int cmd, String val);

	public static native void JavaCallCForInt(int cmd, int val);

}
