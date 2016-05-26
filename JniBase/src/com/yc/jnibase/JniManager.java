/**
 * 
 */
package com.yc.jnibase;

import java.util.ArrayList;
import java.util.List;

/**
 * @author YC
 * @time 2016-5-26 下午2:37:54
 */
public class JniManager implements IJniCall{

	
	private List<IJniCall> jniCallList = new ArrayList<IJniCall>();
	
	private static JniManager mJniManager = null;
	public static JniManager getInstanse(){
		if (mJniManager == null){
			synchronized (mJniManager) {
				if (mJniManager == null){
					mJniManager = new JniManager();
				}
			}
		}
		return mJniManager;
	}
	
	/**注册Jni调用方法*/
	public void registorJniCall(IJniCall call){
		jniCallList.add(call);
	}
	
	/**注销Jni调用方法*/
	public void unregisterJniCall(IJniCall call){
		jniCallList.remove(call);
	}
	
	private JniManager(){
		
	}

	@Override
	public String CCallJavaForString(int cmd, String val) {
		String result = null;
		synchronized (jniCallList) {
			for (IJniCall call : jniCallList) {
				result = call.CCallJavaForString(cmd, val);
				if (result != null){
					break;
				}
			}
		}
		return result;
	}

	@Override
	public boolean CCallJavaForInt(int cmd, int val) {
		synchronized (jniCallList) {
			for (IJniCall call : jniCallList) {
				if (call.CCallJavaForInt(cmd, val)){
					return true;
				}
			}
		}
		return false;
	}

	@Override
	public void JavaCallCForString(int cmd, String val) {
		JniClient.JavaCallCForString(cmd, val);		
	}

	@Override
	public void JavaCallCForInt(int cmd, int val) {
		JniClient.JavaCallCForInt(cmd, val);		
	}
}
