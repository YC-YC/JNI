/*
 * IPC.cpp
 *
 *  Created on: 2018-5-16
 *      Author: YC2
 */

#include "IPC.h"

#include "comdef.h"
#include <string.h>
#include <errno.h>
//#include "Log.h"
//using namespace std;
void* threadHandler(void* param){
	IPC* pIPC = (IPC*)param;
	return (pIPC->threadProc());
}

IPC::IPC(){
		pIPCModle = NULL;
		mMsgCallback = NULL;
		mThreadId = 0;
		m_bThreadRun = false;
		m_bReqExitThread = false;
	}
IPC::~IPC(){
	if (pIPCModle != NULL){
		delete pIPCModle;
		pIPCModle = NULL;
	}
}

void IPC::setIPCModle(IPCModle* pModle){
	pIPCModle = pModle;
}

void IPC::addMsgCallback(MsgCallback* cb){
	mMsgCallback = cb;
}
void IPC::removeMsgCallback(MsgCallback* cb){
	mMsgCallback = NULL;
}
int IPC::startIPC(){
	LOGI("startIPC");
	if( mThreadId <= 0 ){
		m_bReqExitThread = false;
		if( 0!= pthread_create(&mThreadId, NULL, threadHandler, (void*)this) ){
			return -1;
		}
	 }
	 return 0;
}
int IPC::stopIPC(){
	LOGI("stopIPC ---");
	if(m_bThreadRun){
		m_bReqExitThread = true;
		for(int i =0;i < 300;i++){
			if(!m_bThreadRun){
				break;
			}
			Sleep(10);
		}
	}
	mThreadId = 0;
	LOGI("stopIPC +++");
	return 0;
}
int IPC::sendMessage(MESSAGE& msg){
	//LOGI("sendMessage");
	if (pIPCModle != NULL){
		return pIPCModle->sendMessage(msg);
	}
	return 0;
}

void* IPC::threadProc(){
	LOGI("threadProc");
	m_bThreadRun = true;
	if (pIPCModle != NULL){
			pIPCModle->initModle();
	}
	if (pIPCModle != NULL && pIPCModle->canGet()){
		while(!m_bReqExitThread){
			//TODO:get message
			if (pIPCModle != NULL){
				MESSAGE msg;
				memset(&msg, 0, sizeof(MESSAGE));
				if (pIPCModle->getMessage(msg)){
					notifyMsg(msg);
				}
			}

			Sleep(100);
		}
	}
	m_bReqExitThread = false;
	m_bThreadRun = false;
	return 0;
}

void IPC::notifyMsg(MESSAGE& msg){
	LOGI("notifyMsg msg = %d, buff = %s", msg.msgId, msg.buffer);
}

