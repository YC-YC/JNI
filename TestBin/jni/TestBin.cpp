/*
 * SendCanCmdManager.h
 *
 *  Created on: 2017-10-19
 *      Author: YC
 *
 * 生成bin文件push到/system/bin目录下
 *“/system/bin/TestBin 123”运行
 */
//#include "SendCanCmdManager.h"
#include "CS75SendHelper.h"
#include <strings.h>

//SendCanCmdManager gSendCanCmdManager;
CS75SendHelper gCS75SendHelper;
int main(int argc, char* argv[]){
	if (argv != NULL){
		LOGI("main argc = %d, argv = %s", argc, argv[0]);
	}
	else{
		LOGI("main argc = %d", argc);
	}
	BYTE buffer[11]  = {0x01, 0x02, 0x03, 0x04, 0x05};
	gCS75SendHelper.FullSetCanData(0x2F9, buffer, 8);
	gCS75SendHelper.SetCanData(0x2F8, 12, 12, 0xff);
	gCS75SendHelper.SetCanData(0x2F8, 20, 2, 0xff);

	gCS75SendHelper.GetFullCanData(0x2F8, buffer, 11);

	gCS75SendHelper.GetFullCanData(0x2F9, buffer, 11);


//	gSendCanCmdManager.sendCanData(0x2F8, 12, 12, 0xff);
//

}
