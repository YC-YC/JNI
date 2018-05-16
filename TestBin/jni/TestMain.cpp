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
#include "IPC.h"

//#include "IPC_Message.h"
#ifdef __cplusplus
extern "C"
{
#endif

extern int testSendCan();
extern int testJson();
extern int testPollFile();
extern int testScreencap();
extern void testPattern();
extern void testStd();
extern void testInterface();
extern void testFile();

int main(int argc, char* argv[]){
//	testSendCan();
//	testJson();
//	testPollFile();
//	testScreencap();
	testPattern();
	testStd();
	testInterface();
	testFile();
	/*UartHelper* pUartHelper = new UartHelper();
	pUartHelper->openUart();
	while(1){
		usleep(100000);
	}*/

	IPC* pIpc = new IPC();
	pIpc->setIPCModle(new IPCPipe("/cache/myfifo_write", /*NULL*/"/cache/myfifo_read"));
	pIpc->startIPC();
	for(int i = 0; i < 1000; i++){
		usleep(1*1000*1000);
		MESSAGE msg = {i, "Service test"};
		pIpc->sendMessage(msg);
	}
	pIpc->stopIPC();

}

#ifdef __cplusplus
}
#endif
