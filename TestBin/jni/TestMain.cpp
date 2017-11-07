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

/*//SendCanCmdManager gSendCanCmdManager;
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
}*/

#include <dlfcn.h>

typedef int (*pFullSetCanData)(int moduleId, unsigned char* buffer, int length);
typedef int (*pSetCanData)(int moduleId, int index, int length, int what);
typedef int (*pGetFullCanData)(int moduleId, unsigned char* buffer, int length);

int main(int argc, char* argv[]){

	void* lib = dlopen("/system/lib/libSendCan.so", RTLD_LAZY);
	if (lib == NULL){
		LOGI("load lib err");
		return 0;
	}

	pFullSetCanData FullSetCanData = (pFullSetCanData)dlsym(lib, "FullSetCanData");
	pSetCanData SetCanData = (pSetCanData)dlsym(lib, "SetCanData");
	pGetFullCanData GetFullCanData = (pGetFullCanData)dlsym(lib, "GetFullCanData");

	BYTE buffer[11]  = {0x01, 0x02, 0x03, 0x04, 0x05};

	FullSetCanData(0x2F9, buffer, 8);
	SetCanData(0x2F8, 12, 12, 0xff);
	SetCanData(0x2F8, 20, 2, 0xff);

	GetFullCanData(0x2F8, buffer, 11);
	char ch1[256] = {0};
				sprintf(ch1, "0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,",
						buffer[0], buffer[1],buffer[2],buffer[3],buffer[4],
						buffer[5],buffer[6],buffer[7],buffer[8],buffer[9],
						buffer[10]);
		TestLog("buffer is:%s", ch1);

	GetFullCanData(0x2F9, buffer, 11);

	char ch[256] = {0};
			sprintf(ch, "0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,",
					buffer[0], buffer[1],buffer[2],buffer[3],buffer[4],
					buffer[5],buffer[6],buffer[7],buffer[8],buffer[9],
					buffer[10]);
	TestLog("buffer is:%s", ch);

	dlclose(lib);
}
