/*
 * ShmHelper.cpp
 *
 *  Created on: 2018-5-23
 *      Author: YC2
 */
#include "ShmHelper.h"
#include "ShmFunc.h"
#include <errno.h>
#include <pthread.h>

//信号量ID
const int SEM_ID = 0x1000;

void* threadHandler(void* param){
	ShareMemoryHelper* pHelper = (ShareMemoryHelper*)param;
	return (pHelper->observerThreadHandler());
}

ShareMemoryHelper::ShareMemoryHelper(){
	m_pShm = NULL;
	mShmid = 0;
	m_bCreateShm = false;
	m_bCreateReadThread = false;
	m_bThreadRunReq = false;
	m_bThreadRunReq = false;
	memset(&mData, 0, sizeof(Data_st));
	if ((mShmid = getShareMemory(MEMORY_KEY_ID, sizeof(SHAREDATA))) <= 0){
		mShmid = createShareMemory(MEMORY_KEY_ID, sizeof(SHAREDATA));
		if (mShmid > 0){
			printf("create share memory service ok\n");
			m_bCreateShm = true;
		}
		else{
			printf("create share memory service error, no=%d\n", errno);
		}
	}

	if (mShmid > 0){
		m_pShm = attachShareMemory(mShmid);
	}

	if(m_pShm != NULL){
		if (m_bCreateShm){
			printf("init share memory data\n");
			(*m_pShm).semId = 0;
			memset(&(*m_pShm).shmData, 0, sizeof(Data_st));
		}
		if (m_pShm != NULL){
			if ((*m_pShm).semId == 0){
				(*m_pShm).semId = createSemaphore(SEM_ID);
				if ((*m_pShm).semId > 0){
					printf("create Semaphore ok\n");
				}
				else{
					printf("create Semaphore error, no=%d\n", errno);
				}
			}
		}
	}

}
ShareMemoryHelper::~ShareMemoryHelper(){
	m_bThreadRunReq = false;
	if (m_pShm != NULL){
		if ((*m_pShm).semId > 0){
			deleteSemaphore((*m_pShm).semId);
		}

		detachShareMemory(m_pShm);
		if (m_bCreateShm){
			deleteShareMemory((*m_pShm).semId);
		}
	}
}
void ShareMemoryHelper::addShmDataCallback(ShmDataCallback* cb){
	mCBList.push_back(cb);
	if (!m_bCreateReadThread){
		m_bCreateReadThread = true;
		m_bThreadRunReq = true;
		pthread_t threadId = 0;
		pthread_create(&threadId, NULL, threadHandler, NULL);
	}
}
void ShareMemoryHelper::removeShmDataCallback(ShmDataCallback* cb){
	CB_LIST::iterator it = mCBList.begin();
	while(it != mCBList.end()){
		if ((*it) == cb){
			mCBList.erase(it);
			break;
		}
		it++;
	}
	if (mCBList.empty()){
		printf("req exit thread");
		m_bThreadRunReq = false;
	}
}
bool ShareMemoryHelper::getShmData(Data_st& data){
	if (m_pShm != NULL){
		if (getSemaphore((*m_pShm).semId)){
			memcpy(&data.data, &(*m_pShm).shmData, sizeof(Data_st));
			releaseSemaphore((*m_pShm).semId);
			return true;
		}
	}
	return false;

}
bool ShareMemoryHelper::setShmData(Data_st data){
	if (m_pShm != NULL){
		if (getSemaphore((*m_pShm).semId)){
			memcpy(&(*m_pShm).shmData, &data.data, sizeof(Data_st));
			releaseSemaphore((*m_pShm).semId);
			return true;
		}
	}
	return false;
}

void ShareMemoryHelper::notifyDataChange(const Data_st& data){
	CB_LIST::iterator it = mCBList.begin();
	while(it != mCBList.end()){
		(*it)->onDataChange(data);
		it++;
	}
}

void* ShareMemoryHelper::observerThreadHandler(){
	while(m_bThreadRunReq){
		Data_st data;
		memset(&data, 0, sizeof(Data_st));
		getShmData(data);
		if (data.cmd != mData.cmd || strcmp(data.data, mData.data) != 0){
			memcpy(&mData, &data, sizeof(Data_st));
			notifyDataChange(data);
		}
		usleep(50*1000);
	}
	return NULL;
}



