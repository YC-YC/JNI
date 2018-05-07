/*
 * ComCtrl.cpp
 *
 *  Created on: 2018-5-3
 *      Author: YC2
 */
#include "ComCtrl.h"

void* threadUartRx(void* param){
	CComCtrl* pUart = (CComCtrl*)param;
	return (pUart->threadReadUart());
}

CComCtrl::CComCtrl(){
	m_pDataCallback = NULL;
	mComFd = INVALID_HANDLE_VALUE;
	m_bOpen = false;
	m_bThreadRun = false;
	m_bReqExitThread = false;
}
CComCtrl::~CComCtrl(){

}

bool CComCtrl::openUart(const char* fileName,int baudRate){
	mComFd = open(fileName, O_RDWR | O_NOCTTY);
	if (mComFd == INVALID_HANDLE_VALUE){
		LOG("Open Uart %s FAIL,%d", fileName, mComFd);
		return false;
	}
	else{
		if (setUartOpt(mComFd, baudRate, 8, 'N', 1)){
			if (pthread_create(&pRxThread, NULL, threadUartRx, this) != 0) {
				LOG("Create Thread Proc Com Rx error\r\n");
				return false;
			}
			m_bOpen = true;
			return true;
		}
		return false;
	}
}
void CComCtrl::closeUart(){
	if (mComFd != INVALID_HANDLE_VALUE){
		if(m_bThreadRun){
			m_bReqExitThread = true;
			for(int i =0;i < 300;i++){
				Sleep(10);
				if(!m_bThreadRun){
					break;
				}
			}
		}
		pRxThread = NULL;
		m_bOpen = false;
		//CloseHandle(pRxThread);
		pRxThread = NULL;
		close((int)mComFd);
		mComFd = INVALID_HANDLE_VALUE;
		LOG("CloseUart [OK]");
	}
}
bool CComCtrl::isUartOpen(){
	return m_bOpen;
}
bool CComCtrl::writeUart(void const *pRam,int num){
	if (!isUartOpen()){
		return false;
	}
	int len = write(mComFd, pRam, num);
	return (len > 0);

}
void CComCtrl::setUartDataCallback(UartDataCallback* cb){
	m_pDataCallback = cb;
}

void* CComCtrl::threadReadUart(){
	int readNum = 0;
	static unsigned char readData[1024] = {0};
	LOG("[Uart Thread read ] enter while m_fd:.............");
	if(mComFd != INVALID_HANDLE_VALUE){
//		fcntl((int)m_HandleUart, F_SETFL, O_SYNC); // set block mode
		fcntl((int)mComFd, F_SETFL, O_NONBLOCK);//非阻塞
	}
	m_bThreadRun = true;
	while(mComFd != INVALID_HANDLE_VALUE && m_bOpen){
		if(m_bReqExitThread){
			LOG("Thread reqExit");
			break;
		}
		readNum = read((int)mComFd, readData, sizeof(readData));
		LOG("[Uart Thread read ] Read  NUm:%d",readNum);
		if(readNum > 0){
			if (m_pDataCallback != NULL){
				m_pDataCallback->onDataReceive(readData, readNum);
			}
		}

		Sleep(10);
	}
	m_bReqExitThread = false;
	m_bThreadRun = false;
	return NULL;
}

void CComCtrl::printfBuffHex(const unsigned char* buff, int len)
{
//	return;
//	char * printfBuff = NULL;
//	printfBuff = new char[1024 * 3];
//	memset(printfBuff, 0, 1024 * 3);
	char * printfBuff = (char*)calloc(1024 * 3, sizeof(char));
	char Temp[10] = { 0 };
	for (int i = 0; i < len && i < 1024; i++){
		sprintf(Temp, "%02x ", buff[i]);
		strcat(printfBuff, Temp);
	}
	strcat(printfBuff, "\r\n");
	printf("%s", printfBuff);
//	delete printfBuff;
	free(printfBuff);
	printfBuff = NULL;
}

int CComCtrl::setUartOpt(int fd,int speed, int bits, char event, int stop){

	struct termios newtio,oldtio;
	if(tcgetattr( fd,&oldtio) != 0){
		perror("setUartOpt");
		LOG("tcgetattr( fd,&oldtio) -> %d",tcgetattr( fd,&oldtio));
		return 0;
	}

	bzero( &newtio, sizeof( newtio ) );

	/*step1: set charactor size*/
	newtio.c_cflag  |=  CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	/*set stop bit*/
	switch(bits){
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
	 }
	/*set parity bit*/
	switch(event){
		case 'o':
		case 'O': //odd
			newtio.c_cflag |= PARENB;
			newtio.c_cflag |= PARODD;
			newtio.c_iflag |= (INPCK | ISTRIP);
			break;
		case 'e':
		case 'E': //even
			newtio.c_iflag |= (INPCK | ISTRIP);
			newtio.c_cflag |= PARENB;
			newtio.c_cflag &= ~PARODD;
			break;
		case 'n':
		case 'N':  //No parity
			newtio.c_cflag &= ~PARENB;
			break;
		default:
			break;
	 }
	 /*set baud rate*/
	switch(speed){
	  case 57600:
		  cfsetispeed(&newtio, B57600);
		  cfsetospeed(&newtio, B57600);
		  break;
	 case 2400:
		 cfsetispeed(&newtio, B2400);
		 cfsetospeed(&newtio, B2400);
		 break;
	 case 38400:
		 cfsetispeed(&newtio, B38400);
		 cfsetospeed(&newtio, B38400);
		 break;
	 case 4800:
		 cfsetispeed(&newtio, B4800);
		 cfsetospeed(&newtio, B4800);
		 break;
	  case 19200:
		  cfsetispeed(&newtio, B19200);
		  cfsetospeed(&newtio, B19200);
		  break;
	 case 9600:
		 cfsetispeed(&newtio, B9600);
		 cfsetospeed(&newtio, B9600);
		 break;
	 case 115200:
		 cfsetispeed(&newtio, B115200);
		 cfsetospeed(&newtio, B115200);
		 break;
	 case 460800:
		 cfsetispeed(&newtio, B460800);
		 cfsetospeed(&newtio, B460800);
		 break;
	 default:
		 cfsetispeed(&newtio, B9600);
		 cfsetospeed(&newtio, B9600);
		 break;
	 }

	/*set stop bit*/
	if(stop == 1){
		newtio.c_cflag &=  ~CSTOPB;
	}
	else if (stop == 2){
		newtio.c_cflag |=  CSTOPB;
	}

	/*set waiting time*/
	newtio.c_cc[VTIME]  = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush(fd,TCIFLUSH);

	/*enable the config*/
	if((tcsetattr(fd,TCSANOW,&newtio))!=0) {
		perror("com set error");
		return 0;
	}

	LOG("set done!");
	return 1;
}
