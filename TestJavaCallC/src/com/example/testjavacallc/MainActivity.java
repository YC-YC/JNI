package com.example.testjavacallc;

import java.io.File;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.yc.javacallc.IOCtlProxy;
import com.yc.javacallc.SerialPortProxy;
import com.yc.javacallc.SerialPortProxy.OnDataReceiveListener;

public class MainActivity extends Activity implements OnDataReceiveListener{

	
	private static int MDRV_GPIO_RESET = 0x5100;	//输出0
	private static int MDRV_GPIO_SET = 0x5101;	//输出1
	private static int MDRV_GPIO_IN = 0x5102;	//设置为输入
	private static int MDRV_GPIO_OUT = 0x5103;	//设置为输出
	private static int MDRV_GPIO_READ = 0x5104;	//读取io口数据
	
	private static int GPIO_1_0 = (1-1)*32+0;
	private static int GPIO_1_1 = (1-1)*32+1;
	private static int GPIO_2_0 = (2-1)*32+0;
	private static int GPIO_2_1 = (2-1)*32+1;
	private static int GPIO_3_20 = (3-1)*32+20;
	private static int GPIO_3_21 = (3-1)*32+21;
	
	private SerialPortProxy mSerialPortProxy;
	private IOCtlProxy mIoCtlProxy;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}


	public void openSerial(View view){
		if (mSerialPortProxy == null){
			mSerialPortProxy = new SerialPortProxy();
		}
		try {
			mSerialPortProxy.openSerialPort(new File("/dev/ttymxc2"), 38400);
			mSerialPortProxy.setOnDataReceiveListener(this);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void sendCmd(View view)
	{
		if (mSerialPortProxy == null){
			return;
		}
		byte[] buffer = new byte[]{(byte) 0x81,(byte)0x01,(byte)0x23,
				(byte)0x02,(byte)0x03,(byte)0x00,
				(byte)0x02, (byte)0xd2, (byte)0x82};
		
		mSerialPortProxy.sendBuffer(buffer);
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		byte[] buffer2 = new byte[]{(byte) 0x81,(byte)0x03,(byte)0x09,
				(byte)0xf1,(byte)0x82};
		
		mSerialPortProxy.sendBuffer(buffer2);
	}
	
	public void sendCmd2(View view)
	{
		if (mSerialPortProxy == null){
			return;
		}
		byte[] buffer = new byte[]{(byte) 0x81,(byte)0x01,(byte)0x23,
				(byte)0x02,(byte)0x03,(byte)0x00,
				(byte)0x01, (byte)0xd3, (byte)0x82};
		
		mSerialPortProxy.sendBuffer(buffer);
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		byte[] buffer2 = new byte[]{(byte) 0x81,(byte)0x03,(byte)0x09,
				(byte)0xf1,(byte)0x82};
		
		mSerialPortProxy.sendBuffer(buffer2);
	}
	
	public void closeSerial(View view)
	{
		if (mSerialPortProxy == null)
			return;
		mSerialPortProxy.closeSerialPort();
			
	}
	
	public void testIoCtl(View view)
	{
		if (mIoCtlProxy == null)
			return;
		mIoCtlProxy.IOCtl("/dev/zh_dev", MDRV_GPIO_OUT, GPIO_3_20);
	}
	
	@Override
	public void onDataReceive(byte[] buffer, int size) {
		printArray(buffer, size);
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
		Log.i("Receive", result);
	}
	
}
