/**
 * 
 */
package com.yc.javacallc;

import java.io.File;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.util.Log;


/**
 * @author YC
 * @time 2016-6-4 下午3:42:24
 * 串口代理
 */
public class SerialPortProxy {

	private static final String TAG = "SerialPortProxy";
	
	private InputStream mInputStream;
	private OutputStream mOutputStream;
	
	private FileDescriptor mFd = null;
	
	private OnDataReceiveListener mDataReceiveListener = null;  
	
	private ReadThread mReadThread;
	private boolean mIsReadThreadStop = false;
	
	
	public interface OnDataReceiveListener {  
        public void onDataReceive(byte[] buffer, int size);  
    }  
	
	public void setOnDataReceiveListener(OnDataReceiveListener dataReceiveListener) {  
    	mDataReceiveListener = dataReceiveListener;  
    } 
	
	/**打开串口*/
	public void openSerialPort(File path, int baud) throws IOException{
		if (path == null){
			throw new IOException();
		}
		mFd = Connection.open(path.getAbsolutePath(), baud);
		if (mFd == null)
		{
			throw new IOException();
		}
		mInputStream = new FileInputStream(mFd);
		mOutputStream = new FileOutputStream(mFd);
		mReadThread = new ReadThread();
		mIsReadThreadStop = false;
		mReadThread.start();
	}
	
	/**关闭串口*/
	public void closeSerialPort() {
		mIsReadThreadStop = true;
		if (mReadThread != null)
		{
			mReadThread.interrupt();
		}
		if (mFd != null)
		{
			Connection.close();
		}
	}
	
	/**发送字符串*/
	public boolean sendCmd(String cmd) {
		byte[] buffer = cmd.getBytes();
		return sendBuffer(buffer);
	}
	
	/**发送数组*/
	public boolean sendBuffer(byte[] buffer) {
		boolean result = false;
		printArray(buffer, buffer.length);
		try {
			if (mOutputStream != null)
			{
				mOutputStream.write(buffer);
				result = true;
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	private void printArray(byte[] buffer, int size) {
		String result = null;
		for (int i = 0; i < size; i++)
		{
			if (result != null)
			{
//				result = result + Integer.toHexString(buffer[i]&0xFF) + " ";
				result = result + String.format("%02x", buffer[i]&0xFF) + " ";
			}
			else
			{
				result = String.format("%02x", buffer[i]&0xFF) + " ";
			}
		}
		Log.i(TAG, "Send" + result);
	}
	
	private class ReadThread extends Thread {

		@Override
		public void run() {
			super.run();
			while (!mIsReadThreadStop && !isInterrupted()) {
				try {
					int size;
					if (mInputStream != null) {
						byte[] buffer = new byte[256];
						size = mInputStream.read(buffer, 0, 256);
						if (size > 0) {
							if (mDataReceiveListener != null) {
								mDataReceiveListener.onDataReceive(buffer, size);
							}
						}
					}
					Thread.sleep(10);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}
	}
	
}
