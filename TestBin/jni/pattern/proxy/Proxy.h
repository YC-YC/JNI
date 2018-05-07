/*
 * Proxy.h
 *
 *  Created on: 2018-5-3
 *      Author: YC2
 */

#ifndef PROXY_H_
#define PROXY_H_
#include "Log.h"
#include "comdef.h"

class Subject{
public:
	Subject(){}
	virtual ~Subject(){}
	virtual void request() = 0;
};

class ConcreteSubject:public Subject{
public:
	ConcreteSubject(){}
	~ConcreteSubject(){}
	void request(){
		LOGI("ConcreteSubject request");
	}
};

class Proxy:public Subject{
private:
	Subject* m_pSubject;
public:
	Proxy(){m_pSubject = NULL;}
	~Proxy(){}
	void request(){
		if (m_pSubject == NULL){
			m_pSubject = new ConcreteSubject();
		}
		this->doSomeThing1();
		this->m_pSubject->request();
		this->doSomeThing2();
	}
private:
	void doSomeThing1(){
		LOGI("Proxy doSomeThing1");
	}
	void doSomeThing2(){
		LOGI("Proxy doSomeThing2");
	}
};
#endif /* PROXY_H_ */
