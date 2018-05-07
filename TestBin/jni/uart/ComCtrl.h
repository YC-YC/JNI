/*
 * ComCtrl.h
 *
 *  Created on: 2018-5-3
 *      Author: YC2
 */

#ifndef COMCTRL_H_
#define COMCTRL_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <pthread.h>
#include "Log.h"

#define LOGT(tag, fmt, msg...) printf("[%s -- %s]:" fmt "\n", __TIME__, tag, ##msg);
//#define LOG( fmt, msg...) LOGT("CComCtrl", fmt, ##msg)
#define LOG( fmt, msg...) LOGI(fmt, ##msg)
#define INVALID_HANDLE_VALUE	-1

#define Sleep(x) usleep(1000*x);


class UartDataCallback{
public:
	virtual void onDataReceive(const unsigned char data[], int len) = 0;
};

class CComCtrl{
public :
	CComCtrl();
	~CComCtrl();
	bool openUart(const char* fileName,int baudRate = 0); //1->OK 0->FAIL
	void closeUart();
	bool isUartOpen();
	bool writeUart(void const *pRam,int num);
	void setUartDataCallback(UartDataCallback* cb);
	void* threadReadUart();
	void printfBuffHex(const unsigned char* buff, int len);
private:
	int setUartOpt(int fd,int speed, int bits, char event, int stop);
private:
	UartDataCallback* m_pDataCallback;
	int mComFd;
	pthread_t pRxThread;
	bool m_bThreadRun;
	bool m_bOpen;
	bool m_bReqExitThread;
};



#endif /* COMCTRL_H_ */
