/*
 * SendCanCmdManager.h
 *
 *  Created on: 2017-10-19
 *      Author: YC
 */
#include <math.h>
#define LOG_TAG "TestCan"
#define TEST_LOG 0

#include <comdef.h>

#define CAN_DATA_LENGTH 11
#define CAN_DATA_START_OFFSET 3
#define CANBYTEHELPERS_LEN 4

class CanByteHelper{

public:

	CanByteHelper(){
		bValid = false;
		mDataIndex = 0;
		mStartBit = 0;
		mBitLen = 0;
		mData = 0;
	}

	CanByteHelper(int dataIndex, int startBit, int bitLen, BYTE data){
		bValid = true;
		mDataIndex = dataIndex;
		mStartBit = startBit;
		mBitLen = bitLen;
		mData = data;
	}

	bool isDataValid(){
		return bValid;
	}

	int getDataIndex(){
		return mDataIndex;
	}

	BYTE setByte(BYTE byteData){
		BYTE FF = (BYTE)((int)pow(2, mBitLen)-1<<mStartBit);
		byteData = (BYTE)(((~FF )& byteData) |mData);
		return byteData;
	}

	private:
		bool bValid;
		int mDataIndex;
		int mStartBit;
		int mBitLen;
		BYTE mData;
};

class SendModule{
public:
	SendModule(int moduleId){

		pthread_mutex_init(&m_sendMutex, NULL);
		mModuleId = moduleId;
		mBuffer[0] = 0x00;
		mBuffer[1] = (BYTE)((mModuleId>>8) & 0xFF);
		mBuffer[2] = (BYTE)(mModuleId& 0xFF);
	}

	int getModuleId(){
		return mModuleId;
	}

//	void setCanProxy(CanProxy* pCanProxy){
//		m_pCanProxy = pCanProxy;
//	}
	
	void sendCanData(CanByteHelper* canByteHelpers){
		setCanData(canByteHelpers);
//		if (m_pCanProxy != NULL){
//			m_pCanProxy->sendCanDataToMcu(mBuffer, CAN_DATA_LENGTH);
//		}
	}

	void setDefaultCanData(BYTE* buffer, int length){
		pthread_mutex_lock(&m_sendMutex);
		if (length > (CAN_DATA_LENGTH-CAN_DATA_START_OFFSET)){
			length = (CAN_DATA_LENGTH-CAN_DATA_START_OFFSET);
		}
		if (length > 0 && length <= (CAN_DATA_LENGTH-CAN_DATA_START_OFFSET)){
			memcpy(mBuffer+CAN_DATA_START_OFFSET, buffer, sizeof(BYTE)*length);
		}
		printBuffer();
		pthread_mutex_unlock(&m_sendMutex);
	}

	void setCanData(CanByteHelper* canByteHelpers){
		TestLog("setCanData");
		pthread_mutex_lock(&m_sendMutex);
		if (canByteHelpers != NULL){
			for (int i = 0; i < CANBYTEHELPERS_LEN; i++){
				CanByteHelper canByteHelper = canByteHelpers[i];
				if (canByteHelper.isDataValid()){
					int byteIndex = canByteHelper.getDataIndex() + CAN_DATA_START_OFFSET;
//					LOGI("setData byteIndex = %d", byteIndex);
					mBuffer[byteIndex] = canByteHelper.setByte(mBuffer[byteIndex]);
				}
				else{
//					LOGI("break");
					break;
				}
			}
		}
		printBuffer();
		pthread_mutex_unlock(&m_sendMutex);
	}

	int getCanData(unsigned char* buffer, int length){
		TestLog("setCanData");
		pthread_mutex_lock(&m_sendMutex);
		if (buffer != NULL){
			memcpy(buffer, mBuffer, sizeof(BYTE)*CAN_DATA_LENGTH);
		}
		printBuffer();
		pthread_mutex_unlock(&m_sendMutex);
		return CAN_DATA_LENGTH;
	}

private:
	void printBuffer(){
		char ch[256] = {0};
		sprintf(ch, "0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,",
				mBuffer[0], mBuffer[1],mBuffer[2],mBuffer[3],mBuffer[4],
				mBuffer[5],mBuffer[6],mBuffer[7],mBuffer[8],mBuffer[9],
				mBuffer[10]);
		TestLog("buffer is:%s", ch);
	}


private:
	pthread_mutex_t m_sendMutex;
	int mModuleId;
	BYTE mBuffer[CAN_DATA_LENGTH];
//	CanProxy* m_pCanProxy = NULL;
};

class SendCanCmdManager{
public:
	SendCanCmdManager();
	~SendCanCmdManager();
//	void setCanProxy(CanProxy* pCanProxy);
	int defaultCanData(int moduleId, unsigned char* buffer, int length);
	void sendCanData(int moduleId, int index, int length, int what);
	int setCanData(int moduleId, int index, int length, int what);
	int getCanData(int moduleId, unsigned char* buffer, int length);

private:
	
	CanByteHelper* formatCanData(int index, int length, int what);
private:
	pthread_mutex_t m_Mutex;
	
};
