/*
 * Adapter.h
 *	适配模式，偷梁换柱
 *  Created on: 2018-5-4
 *      Author: YC2
 */

#ifndef ADAPTER_H_
#define ADAPTER_H_

#include "Log.h"

class Target{
public:
	virtual int Request(){
		LOGI("Target Request return = %d", 5);
		return 5;
	}
};

class Adaptee{
public:
	int specificRequest(){
		LOGI("Adaptee specificRequest return = %d", 220);
		return 220;
	}
};

//类适配模式，通过public继承获得接口，private继承获得实现
class Adapter:public Target, private Adaptee{
public:
	int Request(){
		int result = this->specificRequest();
		LOGI("Adapter Request return = %d", result);
		return result;
	}
};

class Adapter1:public Target{
public:
	Adapter1(){
		m_pAdaptee = new Adaptee();
	}
	Adapter1(Adaptee* adaptee){
		m_pAdaptee = adaptee;
	}

	int Request(){
		int result = m_pAdaptee->specificRequest();
		LOGI("Adapter1 Request return = %d", result);
		return result;
	}
private:
	Adaptee* m_pAdaptee;
};




#endif /* ADAPTER_H_ */
