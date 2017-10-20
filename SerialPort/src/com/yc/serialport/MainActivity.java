package com.yc.serialport;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.yc.serialport.SerialPortUtils.OnDataReceiveListener;

public class MainActivity extends Activity implements OnDataReceiveListener {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}


	public void openSerial(View view)
	{
		SerialPortUtils.getInstance().openSerialPort("/dev/ttymxc2", 38400);
		SerialPortUtils.getInstance().setOnDataReceiveListener(this);
	}
	
	public void sendCmd(View view)
	{
//		SerialPortUtils.getInstance().sendCmd("ffaa02a401a7");	
//		byte[] buffer = new byte[]{(byte) 0xFF,(byte)0xAA,(byte)0x02,(byte)0xA4,(byte)0x01,(byte)0xA7};
		
		byte[] buffer = new byte[]{(byte) 0x81,(byte)0x01,(byte)0x23,
				(byte)0x02,(byte)0x03,(byte)0x00,
				(byte)0x02, (byte)0xd2, (byte)0x82};
		
		SerialPortUtils.getInstance().sendBuffer(buffer);
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		byte[] buffer2 = new byte[]{(byte) 0x81,(byte)0x03,(byte)0x09,
				(byte)0xf1,(byte)0x82};
		
		SerialPortUtils.getInstance().sendBuffer(buffer2);
	}

	public void sendCmd2(View view)
	{
//		SerialPortUtils.getInstance().sendCmd("ffaa02a401a7");	
//		byte[] buffer = new byte[]{(byte) 0xFF,(byte)0xAA,(byte)0x02,(byte)0xA4,(byte)0x01,(byte)0xA7};
		
		byte[] buffer = new byte[]{(byte) 0x81,(byte)0x01,(byte)0x23,
				(byte)0x02,(byte)0x03,(byte)0x00,
				(byte)0x01, (byte)0xd3, (byte)0x82};
		
		SerialPortUtils.getInstance().sendBuffer(buffer);
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		byte[] buffer2 = new byte[]{(byte) 0x81,(byte)0x03,(byte)0x09,
				(byte)0xf1,(byte)0x82};
		
		SerialPortUtils.getInstance().sendBuffer(buffer2);
	}
	
	public void closeSerial(View view)
	{
		SerialPortUtils.getInstance().closeSerialPort();
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
