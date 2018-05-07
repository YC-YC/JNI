/*
 * Parser.cpp
 *
 *  Created on: 2018-5-4
 *      Author: YC2
 */
#include "Parser.h"
#include "string.h"

#define CLIENT_BUFF_SIZE		(1024*10)
#define CMD_MAX_LEN				(100)	//命令是大长度
void McuParser::inputData(const unsigned char* pData, int len){
	static unsigned char rxBuf[CLIENT_BUFF_SIZE + 1] = { 0 }; //预存数据
	static int rxLen = 0; //未处理数据长度

	if (len < 0){
		return;
	}

//	RETAILMSG(UART_DEBUG, (TEXT("DVR Receive Data:len=[%d]\r\n"), len));
	//拼接数据
	if (rxLen + len > CLIENT_BUFF_SIZE){
		memcpy(rxBuf + rxLen, pData, CLIENT_BUFF_SIZE - rxLen);
		rxLen = CLIENT_BUFF_SIZE;
	}
	else{
		memcpy(rxBuf + rxLen, pData, len);
		rxLen = rxLen + len;
	}
//		RETAILMSG(UART_DEBUG, (TEXT("DVR Receive rxBuf:len=[%d]\r\n"), rxLen));
//		PrintfBuffHex(rxBuf, rxLen);
	if (rxLen < 6) //至少6个才处理（DVR至少6个字节）
	{
		return;
	}
	while (1)
	{
		int Index = findInvalidIndex(rxBuf, rxLen); //查找无效的索引
		if (Index > 0){
			rxLen -= (Index + 1);
			memcpy(rxBuf, &rxBuf[Index], rxLen); //将前面已经无效的内容覆盖掉
		}
		if (!isValidMsg(rxBuf, rxLen)){ //不是有效的消息长度
			break;
		}
		else{
//			RETAILMSG(UART_DEBUG, (TEXT("DVR Have rxBuf:len=[%d]\r\n"), rxLen));
//			PrintfBuffHex(rxBuf, rxLen);
			static unsigned char sCmdData[CMD_MAX_LEN] = { 0 }; //只存DVR接收数据的data
			int cmdLen = 0;
			memset(sCmdData,0, CMD_MAX_LEN);
			cmdLen = rxBuf[2] + 4;
			memcpy(&sCmdData, rxBuf, cmdLen); //取出一条信息

			rxLen -= cmdLen;
			memcpy(rxBuf, &rxBuf[cmdLen], rxLen); //将一条信息删除

//			RETAILMSG(UART_DEBUG,(TEXT("DVR have msg Data,len=[%d]: "), g_MsgLen));
//			PrintfBuffHex(g_MsgData, g_MsgLen);

			unsigned char checksum = sCmdData[cmdLen - 1];
			if (checksum == getCheckSum(&sCmdData[2], cmdLen-3)){
				notifyCmd(sCmdData, cmdLen);
			}
		}
	}
}

int McuParser::findInvalidIndex(const unsigned char* buff, int len){
	int index = 0;
	for (index = 0; index < len; index++) //查找0xFF
	{
		if (buff[index] == 0xFF)
		{
			if (index == len - 1){ //0xFF是最后一个
				break;
			}
			else{
				if (buff[index + 1] == 0xAA){ //0xFF后一个是0xAA

					if (index + 2 < len && buff[index + 2] > 50){ //长度大于50当作无效指令
						continue;
					}
					else{
						return index;
					}
				}
				else{
					continue;
				}
			}
		}
	}
	if (index > 0){
		index--;
	}
	return index;
}

bool McuParser::isValidMsg(const unsigned char* buff, int len){
	if (len < 6){
		return false;
	}
	int msgValidLen = buff[2] + 4;
	if (len < msgValidLen){
		return false;
	}
	else{
		return true;
	}
}


unsigned char McuParser::getCheckSum(unsigned char* buff, int len){
	unsigned char uRet = 0;
	for (int i = 0; i < len; i++){
		uRet += buff[i];
	}
	return uRet;
}

