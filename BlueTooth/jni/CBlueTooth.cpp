/*
 * CBlueTooth.cpp
 *
 *  Created on: 2016-1-12
 *      Author: YC
 */

#include "CBlueTooth.h"
#include "debug.h"

static CBlueTooth* g_pCBlueTooth = NULL;

static void ProcUartRxTemp(const BYTE* buff, int len)
{
	if (g_pCBlueTooth != NULL)
	{
		g_pCBlueTooth->GetUartCom()->ProcRxCmd(buff, len);
	}
}

CBlueTooth::CBlueTooth()
{
	g_pCBlueTooth = this;
	mUartCom = new UartCom();
	mUart = new CUartCtrl();
	OpenUart();
}
CBlueTooth::~CBlueTooth()
{
	if (mUart != NULL)
	{
		delete mUart;
		mUart = NULL;
	}
	if (mUartCom != NULL)
	{
		delete mUartCom;
		mUartCom = NULL;
	}
	g_pCBlueTooth = NULL;
}


UartCom* CBlueTooth::GetUartCom()
{
	return mUartCom;
}

const char* CBlueTooth::GetBlueToothVersion()
{
	return "1.0";
}

void CBlueTooth::OpenUart()	//打开串口
{
	LOGI("OpenUart\r\n");
	if (mUart != NULL)
	{
		LOGI("mUart != NULL\r\n");
		if (!mUart->IsOpen())
		{
			LOGI("!mUart->IsOpen()\r\n");
			mUart->OpenUart(BLUETOOTH_UART_NAME, BLUETOOTH_UART_BAUD);
			mUart->RegRxFun(ProcUartRxTemp);
		}
	}
}
void CBlueTooth::CloseUart()
{
	if (mUart != NULL)
	{
		if (mUart->IsOpen())
		{
			mUart->CloseUart();
		}
	}
}
