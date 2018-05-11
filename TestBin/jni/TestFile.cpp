/*
 * TestFile.cpp
 *	文件测试
 *  Created on: 2018-5-8
 *      Author: YC2
 */

#include "comdef.h"
#include <fstream>
#include <errno.h>

#ifdef __cplusplus
extern "C"
{
#endif

using namespace std;
bool readLine(FILE* fp, char* pLine, int len){
//	int size = sizeof(*pLine);
//	LOGI("readLine size = %d", size);
	memset(pLine, 0 , len);
	fgets(pLine, len-1, fp);
	LOGI("readLine = %s", pLine);
	return true;
}

void testFile(){
	LOGI("testFile");
	LOGI("\n---------C读取-----------\n");

	const char* pFileName = "/storage/udisk/config.cfg";
	//const char* pFileName = "1.txt";
	char line[1000] = {0};
	errno = 0;
	FILE* fp = fopen(pFileName, "r");
	if (fp != NULL){
		while(!feof(fp)){
			readLine(fp, line, 1000);
		}
		fclose(fp);
		fp = NULL;
	}
	else{
		LOGI("open [%s] err[%d]", pFileName, errno);
	}

	LOGI("\n---------C++读取-----------\n");
	ifstream in(pFileName);
	string line2;
	if(in){
		while(getline(in, line2)){
			LOGI("readLine = %s", line2.c_str());
		}
	}
	else{
		LOGI("open [%s] err[%d]", pFileName, errno);
	}

}

#ifdef __cplusplus
}
#endif
