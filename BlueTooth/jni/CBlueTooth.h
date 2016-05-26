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
	void OpenUart();	//�򿪴���
	void CloseUart();

private:
	CUartCtrl* mUart;	//����ͨѶ
	UartCom* mUartCom;	//���մ���

};


#endif /* CBLUETOOTH_H_ */
