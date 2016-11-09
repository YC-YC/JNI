package com.zhonghong.bluetooth;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

import com.example.bluetooth.R;
import com.zhonghong.jni.JniClient;

public class MainActivity extends Activity {
	private static final String TAG = "BlueTooth";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		LOG(JniClient.GetBlueToothVersion());
		
		int[] data = {5};
		LOG("原来数据为：" + data[0]);
		JniClient.updateData(data);
		LOG("更新数据为：" + data[0]);
	}

	private void LOG(String string)
	{
		Log.i(TAG, string);
	}
	
	static{
		System.loadLibrary("BlueTooth");
	}
}
