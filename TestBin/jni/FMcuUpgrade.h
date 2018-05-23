/*
 * FMcuUpgrade.h
 * MCU升级功能类
 *  Created on: 2018-5-19
 *      Author: YC2
 */

#ifndef FMCUUPGRADE_H_
#define FMCUUPGRADE_H_
#include "typedef.h"
#include "CComCtrl.h"

enum ErrorCode{
	FileSizeErr = 0,
	ReadFileErr,
	DVRMode,
	NightMode
};

class McuUpgradeCallback{
public:
	virtual void onUpgradeError(ErrorCode code) = 0;
	virtual void onStartPrepare() = 0;
	virtual void onPrepareOk() = 0;
	virtual void onUpgradeProgress(int total, int progress) = 0;
};

class FMcuUpgrade{
public:
	FMcuUpgrade(INT blocksize = 1028){
		mBlockSize = blocksize;
		m_pBuff = NULL;
		mFileSize = 0;
	}
	~FMcuUpgrade(){}
	void addMcuUpgradeStatusCallback(McuUpgradeCallback* cb){
		mCallback = cb;
	}
	void removeMcuUpgradeStatusCallback(McuUpgradeCallback* cb){
		mCallback = NULL;
	}
	bool sendUpgradeBinToMCU(CComCtrl* com, int index);
	bool isUpgradePackageValid();
	void prepareForUpgrade();
	void inputUpgradeCmd(const BYTE* pCmd, int len);
private:
	bool readMcuUpgradeBin();
	bool saveUpgradeInfo();
	void notifyUpgradeError(ErrorCode code);
	void notifyStartPrepare();
	void notifyPrepareOk();
	void notifyUpgradeProgress(int total, int progress);
private:
	int mBlockSize;
	DWORD mFileSize;
	BYTE* m_pBuff;
	McuUpgradeCallback* mCallback;
};


#endif /* FMCUUPGRADE_H_ */
