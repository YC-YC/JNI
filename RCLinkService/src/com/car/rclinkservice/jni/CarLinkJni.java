/**
 * 
 */
package com.car.rclinkservice.jni;

import android.util.Log;

/**
 * @author YC2
 * @time 2017-9-15 下午5:37:39
 * TODO:
 */
public class CarLinkJni {

	static{
//		System.loadLibrary("Hello");
		Log.e("TestJni", "loadLibrary");
		System.loadLibrary("LinkService");
	}
	
	public static native void CARCInit();
	
	public static native void CARC5msTask();
	
	public static native void CARC10msTask();
	
	
	public static byte[] getRadioList(){
		byte bytes[] = {0x01, 0x02};
		return bytes;
	}
	
	public static byte[] getBtMsg(){
		byte bytes[] = {0x03, 0x04};
		return bytes;
	}
	
	public static byte[] getCanMsg(){
		byte bytes[] = {0x06, 0x05};
		return bytes;
	}
	
	public static boolean putBtMsg(byte[] data){
		if (data != null){
			Log.i("TestJni", String.format("java putBtMsg data len = %d" +
					formatByte(data), data.length));
		}
		return true;
	}
	
	private static String formatByte(byte[] data){
		StringBuilder builder = new StringBuilder("(");
		for(int i = 0; i < data.length; i++){
			builder.append(String.format("0x%x,", data[i]&0xFF));
		}
		builder.append(")");
		return builder.toString();
	}
	
//	extern u8 CARC_GetRadioList(u8 MaxDlc,CARC_RadioInfo_Typedef *pList);//获取收音机搜索列表
//	extern u16 CARC_GetBtMsg(u8 *pData); //获取一包数据
//	extern bool CARC_PutBtMsg(u8 *pData,u16 pLength);//发送一包数据
//	extern u8 CARC_GetCanMsg(CARC_Can_StdMsg_Typedef *pMsg);//获取can信息
	
}
