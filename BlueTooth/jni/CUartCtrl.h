/*
 * CUartCtrl.h
 *
 *  Created on: 2016-1-12
 *      Author: YC
 */

#ifndef CUARTCTRL_H_
#define CUARTCTRL_H_
#include "comdef.h"

typedef void(*UART_READ_FUN)(const BYTE* buf, int len);

class CUartCtrl
{
public:
	CUartCtrl();
	~CUartCtrl();
	bool OpenUart(const char* pPath, unsigned int baud);
	bool IsOpen();
	void CloseUart();
	bool Send(BYTE* buf, int len = -1);
	void ProcRXData(const BYTE* buf, int len);	//接收数据
	void RegRxFun(UART_READ_FUN fun);		//注册接收处理函数
	void ThreadRead();
private:
	bool m_bOpen;
	int mUartfd;
	bool m_bThreadRun;
	bool m_bReqExitThread;
	CRITICAL_SECTION m_csCom;
	UART_READ_FUN m_ReadFun;
	pthread_t m_threadt;

};


#endif /* CUARTCTRL_H_ */
