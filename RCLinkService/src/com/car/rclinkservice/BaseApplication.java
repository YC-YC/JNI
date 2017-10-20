/**
 * 
 */
package com.car.rclinkservice;

import android.app.Application;
import android.util.Log;

import com.car.rclinkservice.jni.CarLinkJni;

/**
 * 
 * @author YC
 * @time 2017-8-9 上午10:59:47
 * TODO:
 */
public class BaseApplication extends Application {
	
	private static final String TAG = "TestJni";

	@Override
	public void onCreate() {
		super.onCreate();
		Log.i(TAG, "onCreate");
		CarLinkJni.CARCInit();
		CarLinkJni.CARC5msTask();
		CarLinkJni.CARC10msTask();
	}
	
}
