/*
 * SendCanCmdManager.h
 *
 *  Created on: 2017-10-19
 *      Author: YC
 */
#include "SendCanCmdManager.h"

const static SendModule gSendModules[] = {
		SendModule(0x296),
		SendModule(0x2F8),
		SendModule(0x2F9),
		SendModule(0x2FA),
		SendModule(0x500),
		SendModule(0x501),
		SendModule(0x513),
		SendModule(0x514),
		SendModule(0x515),
		SendModule(0x51A),
		SendModule(0x527),
		SendModule(0x555),
		SendModule(0x580),
		SendModule(0x600),
		SendModule(0x601),
		SendModule(0x340),
		SendModule(0x580)};

SendCanCmdManager::SendCanCmdManager(){
	pthread_mutex_init(&m_Mutex, NULL);
}

SendCanCmdManager::~SendCanCmdManager(){
}
	
//void SendCanCmdManager::setCanProxy(CanProxy* pCanProxy){
//	pthread_mutex_lock(&m_sendMutex);
//	for (int i = 0; i < sizeof(gSendModules)/sizeof(gSendModules[0]); i++){
//		gSendModules[i].sendCanProxy(pCanProxy);
//	}
//	pthread_mutex_unlock(&m_sendMutex);
//}

int SendCanCmdManager::defaultCanData(int moduleId, unsigned char* buffer, int length){
	int result = 0;
	pthread_mutex_lock(&m_Mutex);
	for (int i = 0; i < sizeof(gSendModules)/sizeof(gSendModules[0]); i++){
		SendModule* pSendModule = (SendModule*)(gSendModules+i);
//		LOGI("moduleId = %d", sendModule.getModuleId());
		if (moduleId == pSendModule->getModuleId()){
//			LOGI("same moduleId, index = %d, length = %d", index, length);
			pSendModule->setDefaultCanData(buffer, length);
			result = true;
			break;
		}
	}
	pthread_mutex_unlock(&m_Mutex);
	return result;
}

void SendCanCmdManager::sendCanData(int moduleId, int index, int length, int what){
	pthread_mutex_lock(&m_Mutex);
	for (int i = 0; i < sizeof(gSendModules)/sizeof(gSendModules[0]); i++){
		SendModule* pSendModule = (SendModule*)(gSendModules+i);
//		LOGI("moduleId = %d", sendModule.getModuleId());
		if (moduleId == pSendModule->getModuleId()){
//			LOGI("same moduleId, index = %d, length = %d", index, length);
			CanByteHelper* pCanByteHelpers = formatCanData(index, length, what);
			pSendModule->sendCanData(pCanByteHelpers);
			break;
		}
	}
	pthread_mutex_unlock(&m_Mutex);
}
int SendCanCmdManager::setCanData(int moduleId, int index, int length, int what){
	int result = 0;
	pthread_mutex_lock(&m_Mutex);
	for (int i = 0; i < sizeof(gSendModules)/sizeof(gSendModules[0]); i++){
		SendModule* pSendModule = (SendModule*)(gSendModules+i);
		if (moduleId == pSendModule->getModuleId()){
			CanByteHelper* pCanByteHelpers = formatCanData(index, length, what);
			pSendModule->setCanData(pCanByteHelpers);
			result = 1;
			break;
		}
	}
	pthread_mutex_unlock(&m_Mutex);
	return result;
}

int SendCanCmdManager::getCanData(int moduleId, unsigned char* buffer, int length){
	int result = 0;
	pthread_mutex_lock(&m_Mutex);
	for (int i = 0; i < sizeof(gSendModules)/sizeof(gSendModules[0]); i++){
		SendModule* pSendModule = (SendModule*)(gSendModules+i);
		if (moduleId == pSendModule->getModuleId()){
			result = pSendModule->getCanData(buffer, length);
			break;
		}
	}
	pthread_mutex_unlock(&m_Mutex);
	return result;
}

CanByteHelper* SendCanCmdManager::formatCanData(int index, int length, int what){
	int dataStartIndex = index/8;
	int dataIndex = dataStartIndex;
	int dataEndIndex = (index + length -1)/8;

	int len = 0;
	int startBit = 0;
	int bitLen = 0;
	static CanByteHelper canByteHelpers[CANBYTEHELPERS_LEN];
	ZeroMemory(canByteHelpers, sizeof(CanByteHelper)*CANBYTEHELPERS_LEN);
	int byteIndex = 0;
	while(dataStartIndex <= dataEndIndex){
		int lessLen  = length - len;
		startBit = index%8;
		int maxBitLen = 8-startBit;
		if (lessLen > maxBitLen){
			bitLen = maxBitLen;
		}
		else{
			bitLen = lessLen;
		}
		BYTE data = (BYTE)(what&((BYTE)(pow(2, bitLen) - 1)));
		data = (BYTE)(data<<startBit);
//		LOGI("dataIndex = %d, startBit = %d, bitLen = %d, data = 0x%x", dataIndex, startBit, bitLen, data);
		canByteHelpers[byteIndex] = CanByteHelper(dataIndex, startBit, bitLen, data);
		byteIndex++;
		what = what >> bitLen;
		len += bitLen;
		index += bitLen;
		dataStartIndex++;
		dataIndex--;
	}
	return canByteHelpers;
}
