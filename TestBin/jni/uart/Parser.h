/*
 * Parser.h
 *
 *  Created on: 2018-5-4
 *      Author: YC2
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <stdio.h>

class CmdCallback{
public:
	virtual void onNotify(const unsigned char* pCmd, int len) = 0;
};

class Parser{
public:
	Parser(){
		mCmdCallback = NULL;
	}
	virtual void inputData(const unsigned char* pData, int len) = 0;
	void setCmdCallback(CmdCallback* cb){
		mCmdCallback = cb;
	}
	void notifyCmd(const unsigned char* pCmd, int len){
		if (mCmdCallback != NULL){
			mCmdCallback->onNotify(pCmd, len);
		}
	}
private:
	CmdCallback* mCmdCallback;
};

class McuParser:public Parser{
public:
	McuParser(){};
	void inputData(const unsigned char* pData, int len);
private:
	int findInvalidIndex(const unsigned char* buff, int len); //查找无效内容的索引
	bool isValidMsg(const unsigned char* buff, int len); //是有效的信息
	unsigned char getCheckSum(unsigned char* buff, int len);
private:

};

#endif /* PARSER_H_ */
