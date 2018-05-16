/*
 * IPCModle.cpp
 *
 *  Created on: 2018-5-16
 *      Author: YC2
 */

#include "IPCModle.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "comdef.h"
#include <errno.h>

IPCPipe::IPCPipe(const char* writePipeName, const char* readPipeName)
	:pWritePath(writePipeName), pReadPath(readPipeName){
	mWriteFd = 0;
	mReadFd = 0;
	if(pWritePath != NULL){
		if (access(pWritePath, F_OK) < 0){
			errno = 0;
			int res = mkfifo(pWritePath, 0660);
			if (res < 0){
				LOGI("IPCPipe mkfifo err = %d, errno = %d", res, errno);
			}
		}
	}
	if(pReadPath != NULL){
		if (access(pReadPath, F_OK) < 0){
			errno = 0;
			int res = mkfifo(pReadPath, 0660);
			if (res < 0){
				LOGI("IPCPipe mkfifo err = %d, errno = %d", res, errno);
			}
		}
	}
}

IPCPipe::~IPCPipe(){
	deInitModle();
}

int IPCPipe::initModle(){
	LOGI("IPCPipe initModle");
	openReadPipe();
	openWritePipe();
	return 0;
}

int IPCPipe::deInitModle(){
	LOGI("IPCPipe deInitModle");
	closePipe(mReadFd);
	closePipe(mWriteFd);
	return 0;
}

int IPCPipe::sendMessage(MESSAGE& msg){
	LOGI("IPCPipe sendMessage");
	openWritePipe();
	if (mWriteFd > 0){
		write(mWriteFd, &msg, sizeof(MESSAGE));
	}
	else{
		LOGI("sendMessage err, no pipe open");
	}
	return 0;
}

int IPCPipe::getMessage(MESSAGE& msg){
	LOGI("IPCPipe getMessage");
	openReadPipe();
	int size = 0;
	if (mReadFd > 0){
		size = read(mReadFd, &msg, sizeof(MESSAGE));
	}
	else{
		LOGI("getMessage err, no pipe open");
	}
	return size;
}

bool IPCPipe::canGet(){
	return (pReadPath != NULL);
}


void IPCPipe::openWritePipe(){
	if (pWritePath != NULL){
		if (mWriteFd <= 0){
			mWriteFd = open(pWritePath, O_WRONLY);
		}
	}
}

void IPCPipe::openReadPipe(){
	if (pReadPath != NULL){
		if (mReadFd <= 0){
			mReadFd = open(pReadPath, O_RDONLY);
		}
	}
}

void IPCPipe::closePipe(int& fd){
	if (fd > 0){
		close(fd);
		fd = 0;
	}
}
