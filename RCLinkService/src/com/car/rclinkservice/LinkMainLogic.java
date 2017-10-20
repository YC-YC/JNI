/**
 * 
 */
package com.car.rclinkservice;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

/**
 * @author YC
 * @time 2017-8-9 上午11:11:13
 * TODO:
 */
public class LinkMainLogic implements IMain {

	protected static final String TAG = "LinkMainLogic";
	private Context mContext;
	private IHandlerThread mMsgHandlerThread;
	private Handler mMsgHandler;
	
	
	@Override
	public void onCreate(Context context) {
		mContext = context;
		mMsgHandlerThread = new IHandlerThread() {
			
			@Override
			public void onHandleMessage(Message msg) {
				switch (msg.what) {
				case 100:
					Log.i(TAG, "has msg 100");
//					Toast.makeText(mContext, "msg 100", Toast.LENGTH_SHORT).show();
					mMsgHandler.sendEmptyMessageDelayed(100, 3*1000);
					break;
				default:
					break;
				}
			}
		};
		mMsgHandler = mMsgHandlerThread.callStart();
		mMsgHandler.sendEmptyMessageDelayed(100, 0);
	}


	@Override
	public void onDestroy() {
		mMsgHandlerThread.callStop();
		mMsgHandlerThread = null;
		mMsgHandler = null;
	}

}
