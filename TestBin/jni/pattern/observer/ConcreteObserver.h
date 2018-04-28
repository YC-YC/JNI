/*
 * ConcreteObserver.h
 *	观察者实现类
 *  Created on: 2018-4-28
 *      Author: YC2
 */

#ifndef CONCRETEOBSERVER_H_
#define CONCRETEOBSERVER_H_

#include "Observer.h"

class ConcreteObserverA:public VirObserver{
public:
	ConcreteObserverA();
	~ConcreteObserverA();
	void onNotify(int cmd);
};

class ConcreteObserverB:public VirObserver{
public:
	ConcreteObserverB();
	~ConcreteObserverB();
	void onNotify(int cmd);
};



#endif /* CONCRETEOBSERVER_H_ */
