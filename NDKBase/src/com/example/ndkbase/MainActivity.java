package com.example.ndkbase;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.logging.SimpleFormatter;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends Activity {

	private static final String TAG = "NdkTest";
	
	 public native String[] getStrings(int count, String sample);
	 
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		String str = NDKClient.HelloJni("", "");
		NDKClient.LoadID3();
		LOG(NDKClient.GetID3Title());
		NDKClient.ReleaseID3();
		NDKClient.SetFilePath("/mnt/sdcard/test.mp3");
		LOG(str);
		LOG("currentTimeMillis " + System.currentTimeMillis());
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-DD hh:mm:ss");
		Date date = new Date(System.currentTimeMillis());
//		Date date = new Date(-28800000);
		LOG("currentTimeMillis " + format.format(date));
	}

	public void doClick(View view)
	{
		switch (view.getId()) {
		case R.id.button1:
			NDKClient.callJavaStaticMethod();
			break;
		case R.id.button2:
			NDKClient.callJavaInstanceMethod();
			break;
		case R.id.button3:
			JavaMethod obj = new JavaMethod();
			obj.setNum(10);
			LOG("Origen Num= " + obj.getNum());
			NDKClient.accessStaticField();
			LOG("After accessStaticField Num= " + obj.getNum());
			break;
		case R.id.button4:
			JavaMethod obj1 = new JavaMethod();
			obj1.setStr("Hello");
			LOG("Origen String= " + obj1.getStr());
			NDKClient.accessInstanceField(obj1);
			LOG("After accessInstanceField String= " + obj1.getStr());
			break;
		case R.id.button5:
			String[] strings = getStrings(100, "I am %d Years Old.");
			for (String str:strings)
			{
				LOG(str);
			}
			break;
		case R.id.button6:
			try {
				NDKClient.exceptionMethod();
			} catch (Exception e) {
				showToast("JNI捕捉到异常");
				e.printStackTrace();
			}
			break;
		default:
			break;
		}
	}
	
	private void LOG(String string){
		Log.e(TAG, string);
	}
	
	private void showToast(String string)
	{
		Toast.makeText(MainActivity.this, string, Toast.LENGTH_SHORT).show();
	}
	
	static{
		System.loadLibrary("NDKBase");
		Log.e(TAG, "loadLibrary NDKBase");
	}
}
