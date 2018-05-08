/*
 * Mediator.h
 *中介者模式(好像并没有什么用)
 *  Created on: 2018-5-6
 *      Author: Administrator
 */

#ifndef MEDIATOR_H_
#define MEDIATOR_H_
#include "Log.h"
#include "comdef.h"

class Colleage;

class Mediator{
public:
	virtual ~Mediator(){}
	virtual void sendMsg(int msg, Colleage* colleage){}
protected:
	Mediator(){}
};

class Colleage{
public:
	~Colleage(){}
	virtual void sendMsg(int);
protected:
	Colleage(Mediator* mediator){
		m_pMediator = mediator;
	}
	Mediator* m_pMediator;
};

class ConcreteColleageA:public Colleage{
public:
	ConcreteColleageA(Mediator* mediator):Colleage(mediator){}
	~ConcreteColleageA(){}
	void sendMsg(int msg){
		LOGI("ConcreteColleageA sendMsg = %d", msg);
		//this->m_pMediator->sendMsg(msg,this);
	}
};

class ConcreteColleageB:public Colleage{
public:
	ConcreteColleageB(Mediator* mediator):Colleage(mediator){}
	~ConcreteColleageB(){}
	void sendMsg(int msg){
		LOGI("ConcreteColleageB sendMsg = %d", msg);
		//this->m_pMediator->sendMsg(msg,this);
	}
};

//中介类管理具体实现类
class ConcreteMediator:public Mediator{
public:
	ConcreteMediator(){
		m_pColleageA = NULL;
	}
	~ConcreteMediator(){
		m_pColleageB = NULL;
	}
	void setColleageA(Colleage* colleage){
		m_pColleageA = colleage;
	}
	void setColleageB(Colleage* colleage){
		m_pColleageB = colleage;
	}
	void sendMsg(int msg, Colleage* colleage){
		if (colleage == m_pColleageA){
			m_pColleageA->sendMsg(msg);
		}
		else if (colleage == m_pColleageB){
			m_pColleageB->sendMsg(msg);
		}
	}
private:
	Colleage* m_pColleageA;
	Colleage* m_pColleageB;

};

#endif /* MEDIATOR_H_ */
