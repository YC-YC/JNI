/*
 * SendCanCmdManager.h
 *
 *  Created on: 2017-10-19
 *      Author: YC
 *
 * 生成bin文件push到/system/bin目录下
 *“/system/bin/TestBin 123”运行
 */

#include <strings.h>
#include <stdio.h>
#include "UartHelper.h"
#ifdef __cplusplus
extern "C"
{
#endif

extern int testSendCan();
extern int testJson();
extern int testPollFile();
extern int testScreencap();
extern void testPattern();

int main(int argc, char* argv[]){
//	testSendCan();
//	testJson();
//	testPollFile();
//	testScreencap();
	testPattern();

	UartHelper* pUartHelper = new UartHelper();
	pUartHelper->openUart();
	while(1){
		usleep(100000);
	}

}

#ifdef __cplusplus
}
#endif
