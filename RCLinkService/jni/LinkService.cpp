#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "Hello.h"
#include "CARC.h"
#include "CCarLink.h"
#include "Log.h"


//static JNIEnv * gEnv = NULL;
static JavaVM *pJavaVm = NULL;

int main(){
	const char* hello = sayHello();
	TestLog("hell");
	TestLog("%s",hello);
	char temp[10] = {0};
	int length = CCarLink::getRadioList(temp);
	TestLog("getRadioList,length=%d,data[%d][%d]",length, temp[0], temp[1]);
	length = CCarLink::getBtMsg(temp);
	TestLog("getBtMsg,length=%d,data[%d][%d]",length, temp[0], temp[1]);
	length = CCarLink::getCanMsg(temp);
	TestLog("getCanMsg,length=%d,data[%d][%d]",length, temp[0], temp[1]);
	bool bResult = CCarLink::putBtMsg(temp, 3);
	TestLog("putBtMsg,bResult=%d",bResult);
	return 0;
}
/**
 * 获取收音机搜索列表
 * MaxDlc:应用层能存放的最大电台数
 * pList:电台信息数组，长度为MaxDlc
 * return:实际电台数
 */
u8 CARC_GetRadioList(u8 MaxDlc,CARC_RadioInfo_Typedef *pList){
	return 0;
}

/**
 * 获取一包数据
 * pData：BT数据，最大长度为36
 * return:FIFO缓存中剩余BT数据的个数，当缓存中没有数据时返回0xFF
 */
u16 CARC_GetBtMsg(u8 *pData){
	return 0;
}

/**
 * 发送一包数据
 * pData:BT数据
 * pLength:最大长度为50
 * return:在写入之前判断底层剩余缓存空间是否大于写入数据空间，若不足，返回FALSE，否则返回TRUE
 */
bool CARC_PutBtMsg(u8 *pData,u16 pLength){
	return false;
}

//获取can信息
/**
 * 获取can信息
 * pMsg:CAN数据
 * return:FIFO缓存中剩余 CAN 消息的个数，当缓存中没有数据时，返回值为 0xFF
 */
u8 CARC_GetCanMsg(CARC_Can_StdMsg_Typedef *pMsg){
	return 0xFF;
}


#ifdef __cplusplus
extern "C" {
#endif

jint JNI_OnLoad(JavaVM* vm, void *reserved)
{
	JNIEnv* env = NULL;
	jint result = -1;

	pJavaVm = vm;

	if(vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
		TestLog("JNI_OnLoad jni fail");
  		return -1;
  	}
	TestLog("JNI_OnLoad jni ok");
	return JNI_VERSION_1_6;
}

//TODO jni函数定义
/*
 * Class:     com_car_rclinkservice_jni_CarLinkJni
 * Method:    CARCInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_car_rclinkservice_jni_CarLinkJni_CARCInit
  (JNIEnv *env, jclass){
	CCarLink::init(pJavaVm, env);
	main();
	TestLog("call CARCInit");
}

/*
 * Class:     com_car_rclinkservice_jni_CarLinkJni
 * Method:    CARC5msTask
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_car_rclinkservice_jni_CarLinkJni_CARC5msTask
  (JNIEnv *, jclass){
	TestLog("call CARC5msTask");
}

/*
 * Class:     com_car_rclinkservice_jni_CarLinkJni
 * Method:    CARC10msTask
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_car_rclinkservice_jni_CarLinkJni_CARC10msTask
  (JNIEnv *, jclass){
	TestLog("call CARC10msTask");

}

/*
 * Class:     com_car_rclinkservice_jni_CarLinkJni
 * Method:    setRadioBytes
 * Signature: ([BI)V
 */
JNIEXPORT void JNICALL Java_com_car_rclinkservice_jni_CarLinkJni_setRadioBytes
  (JNIEnv *env, jclass, jbyteArray buffer, jint len){
	TestLog("setRadioBytes");
}

#ifdef __cplusplus
}
#endif
