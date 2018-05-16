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
#include "comdef.h"
#include "IPC.h"

//#include "IPC_Message.h"
#ifdef __cplusplus
extern "C"
{
#endif

int main(int argc, char* argv[]){

	IPC* pIpc = new IPC();
	pIpc->setIPCModle(new IPCPipe(/*NULL*/"/cache/myfifo_read", "/cache/myfifo_write"));
	pIpc->startIPC();
	for(int i = 0; i < 1000; i++){
		usleep(1*1000*1000);
		MESSAGE msg = {i, "client test"};
		pIpc->sendMessage(msg);
	}
	pIpc->stopIPC();

}

#ifdef __cplusplus
}
#endif
