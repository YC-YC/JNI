/*
 * UartHelper.cpp
 *
 *  Created on: 2018-5-4
 *      Author: YC2
 */

#include "UartHelper.h"

UartHelper::UartHelper(){
	mParser = new McuParser();
	mComCtrl = new CComCtrl();
	mComCtrl->setUartDataCallback(this);
}
UartHelper::~UartHelper(){
	delete mComCtrl;
	mComCtrl = NULL;
	delete mParser;
	mParser = NULL;
}
void UartHelper::onDataReceive(const unsigned char data[], int len){
	mParser->inputData(data, len);
}
void UartHelper::setCmdCallback(CmdCallback* cb){
	mParser->setCmdCallback(cb);
}

bool UartHelper::openUart(){
	return mComCtrl->openUart("/dev/ttymxc4", 115200);
}
void UartHelper::closeUart(){
	mComCtrl->closeUart();
}

