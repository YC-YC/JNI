/**
 * 
 */
package com.yc.jnibase;

/**
 * @author YC
 * @time 2016-5-26 下午2:57:29
 * JNI方法
 */
public interface IJniCall {
	/**如果有处理则返回非null，对于返回结果本来是null的，返回“”*/
	public String CCallJavaForString(int cmd, String val);
	
	/**如果有处理则返回true*/
	public boolean CCallJavaForInt(int cmd, int val);
	
	public void JavaCallCForString(int cmd, String val);
	public void JavaCallCForInt(int cmd, int val);

}
