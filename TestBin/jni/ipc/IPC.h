/*
 * IPC.h
 *
 *  Created on: 2018-5-16
 *      Author: YC2
 */

#ifndef IPC_H_
#define IPC_H_

#include "IPCModle.h"
#include <pthread.h>

//using namespace std;

class MsgCallback{
public:
	virtual void onNotityMsg(MESSAGE* msg) = 0;
};

class IPC{
public:
	IPC();
	~IPC();
	void setIPCModle(IPCModle*);
	void addMsgCallback(MsgCallback*);
	void removeMsgCallback(MsgCallback*);
	int startIPC();
	int stopIPC();
	int sendMessage(MESSAGE&);
	void* threadProc();

private:
	void notifyMsg(MESSAGE&);

private:
	IPCModle* pIPCModle;
	MsgCallback* mMsgCallback;
    pthread_t mThreadId;
    bool m_bThreadRun;
    bool m_bReqExitThread;
};


#endif /* IPC_H_ */
