/*
 * UartCom.cpp
 *
 *  Created on: 2016-1-13
 *      Author: YC
 */
#include "UartCom.h"
#include "debug.h"

const char* CJavaForString(int cmd, const char*val);

UartCom::UartCom()
{

}
UartCom::~UartCom()
{

}
void UartCom::ProcRxCmd(const BYTE* buf, int len)
{
	static BYTE rxBuf[CLIENT_BUFF_SIZE + 1] = {0};
	static int rxLen = 0;	//未处理数据长度
	if (rxLen <= 0)
	{
		return;
	}
	if (rxLen + len > CLIENT_BUFF_SIZE)
	{
		CopyMemory(rxBuf + rxLen, buf, CLIENT_BUFF_SIZE - rxLen);
		rxLen = CLIENT_BUFF_SIZE;
	}
	else
	{
		CopyMemory(rxBuf + rxLen, buf, len);
		rxLen += len;
	}
	PrintBufferHex(buf, len);

	while(1)
	{

	}
}

void UartCom::PrintBufferHex(const BYTE* buf, int len)	//打印接收到的信息
{
	int newLen = 1024;
	char* printbuff = new char[newLen];
	ZeroMemory(printbuff, newLen);
	char temp[10] = {0};
	for (int i = 0; i < len && i < newLen-2; i++)
	{
		ZeroMemory(temp, 10);
		sprintf(temp, "%02x ", buf[i]);
		strcat(printbuff, temp);
	}
	strcat(printbuff, "\r\n");
//	printf("%s", printbuff);
	LOGI("Receive:%s", printbuff);
	delete printbuff;
	printbuff = NULL;
}
