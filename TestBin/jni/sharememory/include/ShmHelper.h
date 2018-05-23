/*
 * ShmHelper.h
 *
 *  Created on: 2018-5-23
 *      Author: YC2
 */

#ifndef SHMHELPER_H_
#define SHMHELPER_H_
#include "ShmComdef.h"
#include <list>



class ShmDataCallback{
public:
	virtual void onDataChange(const Data_st& data) = 0;
};



class ShareMemoryHelper{
public:
	ShareMemoryHelper();
	~ShareMemoryHelper();
	void addShmDataCallback(ShmDataCallback* cb);
	void removeShmDataCallback(ShmDataCallback* cb);
	bool getShmData(Data_st& data);
	bool setShmData(Data_st data);
	friend void* threadHandler(void* param);
private:
	void* observerThreadHandler();
	void notifyDataChange(const Data_st& data);

private:
	typedef std::list<ShmDataCallback *> CB_LIST;
	CB_LIST mCBList;
	SHAREDATA *m_pShm;
	Data_st mData;
	int mShmid;
	bool m_bCreateShm;	//是否创建了Shm
	bool m_bCreateReadThread;
	bool m_bThreadRunReq;
};




#endif /* SHMHELPER_H_ */
