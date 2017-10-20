package com.yc.serialport;

import java.io.File;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;


/**
 * @author YC
 * @time 2016-3-7 下午7:45:35
 */
public class SerialPort {

	private FileDescriptor mFd;
	private FileInputStream mFileInputStream;
	private FileOutputStream mFileOutputStream;
	
	public SerialPort(File device, int baudrate) throws IOException{
		mFd = open(device.getAbsolutePath(), baudrate);
		if (mFd == null)
		{
			throw new IOException();
		}
		mFileInputStream = new FileInputStream(mFd);
		mFileOutputStream = new FileOutputStream(mFd);
	}
	
	/**
	 * 获取输入流
	 * @return
	 */
	public InputStream getInputStream() {
		return mFileInputStream;
	}


	/**
	 * 获取输出流
	 * @return
	 */
	public OutputStream getOutputStream() {
		return mFileOutputStream;
	}


	private native FileDescriptor open(String path, int baudrate);
	
	/**
	 * 关闭串口
	 * @return
	 */
	public native int close();
	
	static {
		System.loadLibrary("SerialPort");
	}
}