package com.example.scanfile;

import java.io.File;

import android.app.Activity;
import android.os.Bundle;
import android.os.SystemClock;
import android.util.Log;
import android.view.View;

public class MainActivity extends Activity {

	protected static final String TAG = "ScanFile";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}
	
	public void doClick(View view){
		new Thread(new Runnable() {
			
			@Override
			public void run() {
				String dir = "/mnt/USB1/testfile";
				File file = new File(dir);
				if (file.exists()){
					long realtime = SystemClock.elapsedRealtime();
					Log.i(TAG, "java list file ------");
					File[] listFiles = file.listFiles();
					Log.i(TAG, "java list file ++++++ take = " + (SystemClock.elapsedRealtime() - realtime));
					long folderSize = 0;
					long folderHashCode = 0;
					realtime = SystemClock.elapsedRealtime();
					Log.i(TAG, "get file info ------");
					if (listFiles != null){
						for(File f: listFiles){
							folderSize += f.length();
							folderHashCode += f.hashCode();
						}
					}
					Log.i(TAG, "get file info ++++++ take = " + (SystemClock.elapsedRealtime() - realtime));
					
					realtime = SystemClock.elapsedRealtime();
					Log.i(TAG, "c list file ------");
					FileJni.listImpl(dir);
					Log.i(TAG, "c list file ++++++ take = " + (SystemClock.elapsedRealtime() - realtime));
				}
			}
		}).start();
	}

}
