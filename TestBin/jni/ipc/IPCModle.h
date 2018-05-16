/*
 * IPCModle.h
 *
 *  Created on: 2018-5-16
 *      Author: YC2
 */

#ifndef IPCMODLE_H_
#define IPCMODLE_H_

//using namespace std;

#define BUFFER          256

typedef struct msg_st{
	long msgId;
	char buffer[BUFFER];
}MESSAGE;

class IPCModle{
public:
	virtual int initModle() = 0;
	virtual int deInitModle() = 0;
	virtual int sendMessage(MESSAGE&) = 0;
	virtual int getMessage(MESSAGE&) = 0;
	virtual bool canGet() = 0;

};

//有名管道
class IPCPipe:public IPCModle{
public:
	IPCPipe(const char* writePipeName, const char* readPipeName);
	~IPCPipe();
	virtual int initModle();
	virtual int deInitModle();
	virtual int sendMessage(MESSAGE&);
	virtual int getMessage(MESSAGE&);
	virtual bool canGet();
private:
	void openWritePipe();
	void openReadPipe();
	void closePipe(int& fd);
private:
	const char* pReadPath;
	const char* pWritePath;
	int mWriteFd;
	int mReadFd;

};

#endif /* IPCMODLE_H_ */
