/**
 * 
 */
package com.car.rclinkservice.service;

import com.car.rclinkservice.IMain;
import com.car.rclinkservice.LinkMainLogic;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

/**
 * adb shell am startservice -a action --es key val --ei key val
 * adb shell am stopservice -a action
 * @author YC
 * @time 2017-8-9 上午10:58:07
 * TODO:
 */
public class LinkService extends Service {

	private static final String TAG = "LinkService";
	
	private IMain mMainLogic;

	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}
	
	//只在服务创建的时候调用
	@Override
	public void onCreate() {
		Log.i(TAG, "onCreate");
		super.onCreate();
		mMainLogic = new LinkMainLogic();
		mMainLogic.onCreate(this);
	}

	//每次调用StartService都会调用
	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		Log.i(TAG, "onStartCommand");
		flags = START_STICKY;
		return super.onStartCommand(intent, flags, startId);
	}
	
	@Override
	public void onDestroy() {
		Log.i(TAG, "onDestroy");
		mMainLogic.onDestroy();
		super.onDestroy();
	}

	@Override
	public void onLowMemory() {
		Log.i(TAG, "onLowMemory");
		super.onLowMemory();
	}

}
