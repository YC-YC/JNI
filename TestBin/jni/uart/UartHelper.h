/*
 * UartHelper.h
 *
 *  Created on: 2018-5-4
 *      Author: YC2
 */

#ifndef UARTHELPER_H_
#define UARTHELPER_H_
#include "Parser.h"
#include "ComCtrl.h"

class UartHelper:public UartDataCallback{
public:
	UartHelper();
	~UartHelper();
	void onDataReceive(const unsigned char data[], int len);
	void setCmdCallback(CmdCallback* cb);
	bool openUart();
	void closeUart();
private:
	CComCtrl* mComCtrl;
	Parser* mParser;

};


#endif /* UARTHELPER_H_ */
