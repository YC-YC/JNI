/*
 * FMcuUpgrade.cpp
 *
 *  Created on: 2018-5-19
 *      Author: YC2
 */
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include "FMcuUpgrade.h"

//mcu升级文件
#define UPDATE_MCU_PATH  "/mnt/sda1/test_mcu_upgrade/update.bin"
//强制升级文件
#define MCU_FORCE_UPGRADE_PATH  "/mnt/sda1/test_mcu_upgrade/force_update.txt"
//记录升级文件信息
#define MCU_UPGRADE_INFO_PATH  "/mnt/backup/mcu_upgrade_info.txt"

bool checkFileExist(const char *file_path);
unsigned long int getFileLastModifyTime(const char *file_path);

bool FMcuUpgrade::sendUpgradeBinToMCU(CComCtrl* com, int index){

	if (com != NULL && com->isUartOpen()){
		void* pSendBuf = calloc(sizeof(BYTE), mBlockSize);
		memcpy(pSendBuf, (void*)m_pBuff[(index-1)*mBlockSize], mBlockSize);
		if (com->writeUart(pSendBuf, mBlockSize)){
			notifyUpgradeProgress(mFileSize, index*mBlockSize);
			return true;
		}
	}
	return false;
}

bool FMcuUpgrade::isUpgradePackageValid(){
	if (!checkFileExist(UPDATE_MCU_PATH)){
		return false;
	}
	if (checkFileExist(MCU_FORCE_UPGRADE_PATH)){
		return true;
	}
	if (checkFileExist(MCU_UPGRADE_INFO_PATH)){
		char buffer[100] = {0};
		FILE *fp = fopen(MCU_UPGRADE_INFO_PATH, "r");
		if (fp == NULL){
			return true;
		}
		fseek(fp, SEEK_SET, 0);
		fgets(buffer, 100-1, fp);
		printf("%s\n", buffer);
		fclose(fp);
		long saveTime = atol(buffer);
		return (saveTime != getFileLastModifyTime(UPDATE_MCU_PATH));
	}
	return true;

}
void FMcuUpgrade::prepareForUpgrade(){
	notifyStartPrepare();
	if (readMcuUpgradeBin()){
		notifyPrepareOk();
	}
}

void FMcuUpgrade::inputUpgradeCmd(const BYTE* pCmd, int len){
	BYTE idx = pCmd[1];//idx为1开始
	BYTE cmd = pCmd[3];
	switch(cmd){
		case 0x06://ACK请求包（正确接送上一包，请求发送下一包）
			if (idx == mFileSize/mBlockSize){	//最后一包时保存数据
				saveUpgradeInfo();
			}
			sendUpgradeBinToMCU(NULL, idx+1);
			break;
		case 0x15://NAK重发（请求重发当前包，握手成功后会先收到这个指令开始发第一包）
			sendUpgradeBinToMCU(NULL, idx);
			break;
		case 0x18://CAN无条件停止
			break;
		default:
			break;
	}

}

bool FMcuUpgrade::saveUpgradeInfo(){
	long modifyTime = getFileLastModifyTime(UPDATE_MCU_PATH);
	char buffer[100] = {0};
	sprintf(buffer,"%l", modifyTime);
	int len = strlen(buffer);
	if (len <= 0){
		return false;
	}
	FILE *fp = fopen(MCU_UPGRADE_INFO_PATH, "w");
	if (fp == NULL){
		return false;
	}
	fseek(fp, SEEK_SET, 0);
	fwrite(buffer,sizeof(char), len, fp);
	int fd = fileno(fp);
	if (fd > 0){
		//sync to disk
		if (fsync(fd) == -1){
			printf("fsync failed!, errno = %d\n", errno);
			if (errno == EIO){
				//fprintf (stderr, ”I/O error on %d!\n”, fd);
			}
		}
	}
	fclose(fp);
	return true;
}
bool FMcuUpgrade::readMcuUpgradeBin(){

	FILE *fp = fopen(UPDATE_MCU_PATH, "rb");
	if(fp != NULL){
		//printf("before copy  time is %d \n", kzsTimeGetCurrentTimestamp());
		fseek(fp, 0, SEEK_END);
		mFileSize = ftell(fp);
		printf("read file size = %d \n", mFileSize);
		if (mFileSize <= 0){
			notifyUpgradeError(FileSizeErr);
			fclose(fp);
			return false;
		}
		m_pBuff = new BYTE[mFileSize];
		fseek(fp, 0, SEEK_SET);
		DWORD rt = fread((void*)m_pBuff,sizeof(BYTE), mFileSize, fp);
		fclose(fp);
		fp = NULL;
		//printf("after copy time is %d \n", kzsTimeGetCurrentTimestamp());

		if(rt != mFileSize){
			notifyUpgradeError(ReadFileErr);
			return 0;
		}
		return true;
	}
	return false;
}

void FMcuUpgrade::notifyUpgradeError(ErrorCode code){
	if (mCallback != NULL){
		mCallback->onUpgradeError(code);
	}
}
void FMcuUpgrade::notifyStartPrepare(){
	if (mCallback != NULL){
			mCallback->onStartPrepare();
		}
}
void FMcuUpgrade::notifyPrepareOk(){
	if (mCallback != NULL){
			mCallback->onPrepareOk();
		}
}
void FMcuUpgrade::notifyUpgradeProgress(int total, int progress){
	if (mCallback != NULL){
			mCallback->onUpgradeProgress(total, progress);
		}
}


bool checkFileExist(const char *file_path){
	return((file_path != NULL) && access(file_path,F_OK) == 0);
}

long getFileLastModifyTime(const char *file_path){
	if (file_path == NULL){
		return 0;
	}
	struct stat sb;
	stat(file_path, &sb);
	return sb.st_mtime;
}
