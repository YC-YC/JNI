/**
 * 
 */
package com.car.rclinkservice;

import android.os.Handler;
import android.os.HandlerThread;
import android.os.Message;

/**
 * 对HandlerThread进行封装
 * @author YC
 * @time 2017-8-9 上午11:20:40
 * TODO:
 */
public abstract class IHandlerThread {

	private HandlerThread mMsgThread;
	private Handler mMsgHandler;
	
	public abstract void onHandleMessage(Message msg);
	
	private void initMsgHandlerThread() {
		mMsgThread = new HandlerThread("yc_check_msg");
		mMsgThread.start();
		
		mMsgHandler = new Handler(mMsgThread.getLooper()){
			
			@Override
			public void handleMessage(Message msg) {
				onHandleMessage(msg);
			};
		};		
	}
	
	public Handler callStart(){
		initMsgHandlerThread();
		return mMsgHandler;
	}
	
	public void callStop(){
		mMsgThread.quit();
	}
}
