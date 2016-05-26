/*
 * CUartCtrl.cpp
 *
 *  Created on: 2016-1-12
 *      Author: YC
 */

#include "CUartCtrl.h"
#include <fcntl.h>
#include <termios.h>
#include "comdef.h"
#include "debug.h"

static void* ThreadRun(void* lParam)
{
	CUartCtrl* uart = (CUartCtrl*)lParam;
	uart->ThreadRead();
	return NULL;
}

CUartCtrl::CUartCtrl()
{
	m_bOpen = false;
	m_ReadFun = NULL;
	mUartfd = 0;
	m_bThreadRun = false;
	m_bReqExitThread = false;
	m_threadt = 0;
	InitializeCriticalSection(&m_csCom);
	LOGI("Start UartCtrl\r\n");
}
CUartCtrl::~CUartCtrl()
{
	CloseUart();
	DeleteCriticalSection(&m_csCom);
}
bool CUartCtrl::OpenUart(const char* pPath, unsigned int baud)
{
	if (pPath != NULL)
	{
		LOGI("OpenUart path=[%s], band=[%d]\r\n", pPath, baud);
		mUartfd = open(pPath, O_RDWR|O_NOCTTY);
		if (mUartfd < 0)
		{
			m_bOpen = false;
//			printf("UartCtrl open error!\r\n");
			LOGI("UartCtrl open error!\r\n");
			return false;
		}
		else
		{
			struct termios oldtio, newtio;
			tcgetattr(mUartfd, &oldtio);	//获取属性
			bzero(&newtio, sizeof(newtio));

//			newtio.c_cflag = baud | CS8 | CLOCAL | CREAD | CSTOPB; //2个停止位CSTOPB
			newtio.c_cflag = baud | CS8 | CLOCAL | CREAD ;
			newtio.c_iflag = 0;
			newtio.c_oflag = 0;
			newtio.c_lflag = 0;
			newtio.c_cc[VTIME] = 0;
			newtio.c_cc[VMIN] = 1;//组合使用，有超过1个数据时才读
			tcflush(mUartfd, TCIOFLUSH);	//清空IO状态
			tcsetattr(mUartfd, TCSANOW, &newtio);	//立即更新
			if (m_threadt == 0)
			{
				m_bOpen = true;
				pthread_create(&m_threadt,NULL,ThreadRun,this);
			}
		}
	}

	return false;
}

bool CUartCtrl::IsOpen()
{
	return m_bOpen;
}
void CUartCtrl::CloseUart()
{
	EnterCriticalSection(&m_csCom);
	if (m_bThreadRun)
	{
		m_bReqExitThread = true;
		for (int i = 0; i < 300; ++i) {
			usleep(10);
			if (!m_bThreadRun)
			{
				break;
			}
		}
		m_ReadFun = NULL;
		m_bOpen = false;

	}
	m_threadt = 0;
	close(mUartfd);
	LeaveCriticalSection(&m_csCom);
}
bool CUartCtrl::Send(BYTE* buf, int len)
{
	if (!m_bOpen)
	{
		return false;
	}
	int i = write(mUartfd, buf, len);
	if (i == len)
	{
		return true;
	}
	return false;
}
void CUartCtrl::ProcRXData(const BYTE* buf, int len)
{
	if (m_ReadFun != NULL)
	{
		m_ReadFun(buf, len);
	}
}
void CUartCtrl::RegRxFun(UART_READ_FUN fun)
{
	m_ReadFun = fun;
}

void CUartCtrl::ThreadRead()
{
	static BYTE readbuf[1024] = {0};
	int readNum = 0;
	if (mUartfd != 0)
	{
//		fcntl(mUartfd, F_SETFL, O_SYNC); //set block,O_NONBLOCK
		fcntl(mUartfd, F_SETFL, O_NONBLOCK); //非阻塞
	}
	LOGI("ThreadRead Start!\r\n");
	m_bThreadRun = true;
	while(mUartfd != 0 && m_bOpen)
	{
		if (m_bReqExitThread)
		{
			break;
		}
		readNum = read(mUartfd, readbuf, sizeof(readbuf));
//		sleep(10);
		static int i = 0;
		i++;
		if ((i%10) == 5)
		{
			CJavaForString(100, "I am from C thread!");
		}
//		LOGI("readNum=[%d]\r\n", readNum);
		if (readNum > 0)
		{
			ProcRXData(readbuf, readNum);
		}
		usleep(10);
	}
	LOGI("ThreadRead End！\r\n");
	m_bReqExitThread = false;
	m_bThreadRun = false;
}
