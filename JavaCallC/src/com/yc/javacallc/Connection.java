/**
 * 
 */
package com.yc.javacallc;

import java.io.FileDescriptor;

/**
 * @author YC
 * @time 2016-6-4 下午3:36:17
 * Java与C通讯的门户
 */
public class Connection {

	/**打开串口*/
	public static native FileDescriptor open(String path, int baudrate);
	/** 关闭串口 */
	public static native int close();
	
	/**IOCtl*/
	public static native int IOCtl(String path, int type, int val);
	
	static {
		System.loadLibrary("JavaCallC");
	}
}
