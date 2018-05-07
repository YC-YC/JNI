/*
 * Bridge.h
 *
 *  Created on: 2018-5-7
 *      Author: Administrator
 */

#ifndef BRIDGE_H_
#define BRIDGE_H_
#include "Log.h"
//实现
class Implement{
public:
virtual ~Implement(){
	LOGI("~Implement");
}
virtual void action() = 0;
protected:
Implement(){
	LOGI("Implement");
}
};

class ConcreteImplememtA:public Implement{
public:
	ConcreteImplememtA(){
		LOGI("ConcreteImplememtA");
	}
	~ConcreteImplememtA(){
		LOGI("~ConcreteImplememtA");
	}
	void action(){
		LOGI("ConcreteImplememtA action");
	}
};

class ConcreteImplememtB:public Implement{
public:
	ConcreteImplememtB(){
		LOGI("ConcreteImplememtB");
	}
	~ConcreteImplememtB(){
		LOGI("~ConcreteImplememtB");
	}
	void action(){
		LOGI("ConcreteImplememtB action");
	}
};

//抽象类
class Abstraction{
public:
virtual ~Abstraction(){
	LOGI("~Abstraction");
}
virtual void action() = 0;
protected:
Abstraction(){
	LOGI("Abstraction");
}
};

class ConcreteAbstractionA:public Abstraction{
public:
	ConcreteAbstractionA(Implement* pImpl):m_pImpl(pImpl){
		LOGI("ConcreteAbstractionA");
	}
	~ConcreteAbstractionA(){
		LOGI("ConcreteAbstractionA");
	}
	void action(){
		LOGI("ConcreteAbstractionA action");
		m_pImpl->action();
	}
private:
	Implement* m_pImpl;
};

class ConcreteAbstractionB:public Abstraction{
public:
	ConcreteAbstractionB(Implement* pImpl):m_pImpl(pImpl){
		LOGI("ConcreteAbstractionB");
	}
	~ConcreteAbstractionB(){
		LOGI("ConcreteAbstractionB");
	}
	void action(){
		LOGI("ConcreteAbstractionB action");
		m_pImpl->action();
	}
private:
	Implement* m_pImpl;
};

#endif /* BRIDGE_H_ */
