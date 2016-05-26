/*
 * CBlueTooth.h
 *
 *  Created on: 2016-1-12
 *      Author: YC
 */

#ifndef CBLUETOOTH_H_
#define CBLUETOOTH_H_
#include "asm/termbits.h"
#include "CUartCtrl.h"
#include "UartCom.h"

//#define BLUETOOTH_UART_NAME		"/dev/ttyS3"
//#define BLUETOOTH_UART_BAUD		B9600

#define BLUETOOTH_UART_NAME		"/dev/ttyS0"
#define BLUETOOTH_UART_BAUD		B115200

class CBlueTooth
{
public:

	CBlueTooth();
	~CBlueTooth();
	UartCom* GetUartCom();
	const char* GetBlueToothVersion();

private:
	void OpenUart();	//打开串口
	void CloseUart();

private:
	CUartCtrl* mUart;	//串口通讯
	UartCom* mUartCom;	//接收处理

};


#endif /* CBLUETOOTH_H_ */
