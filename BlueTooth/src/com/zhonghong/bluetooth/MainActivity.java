package com.zhonghong.bluetooth;

import com.example.bluetooth.R;
import com.zhonghong.jni.JniClient;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;

public class MainActivity extends Activity {
	private static final String TAG = "BlueTooth";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		LOG(JniClient.GetBlueToothVersion());
	}

	private void LOG(String string)
	{
		Log.i(TAG, string);
	}
	
	static{
		System.loadLibrary("BlueTooth");
	}
}
