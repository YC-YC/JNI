/*
 * SendCanCmdManager.h
 *
 *  Created on: 2017-10-19
 *      Author: YC
 *
 * 生成bin文件push到/system/bin目录下
 *“/system/bin/TestBin 123”运行
 */
#include "SendCanCmdManager.h"
#include <strings.h>

SendCanCmdManager gSendCanCmdManager;

int main(int argc, char* argv[]){
	if (argv != NULL){
		LOGI("main argc = %d, argv = %s", argc, argv[0]);
	}
	else{
		LOGI("main argc = %d", argc);
	}

	gSendCanCmdManager.sendCanData(0x2F8, 12, 12, 0xff);

	gSendCanCmdManager.sendCanData(0x2F8, 20, 2, 0xff);

}
