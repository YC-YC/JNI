/*
 * TestPattern.cpp
 *设置模式测试
 *  Created on: 2018-4-16
 *      Author: YC2
 */

#include "comdef.h"
#include "Csingleton.h"
#include "Observer.h"
#include "ConcreteObserver.h"
#include "ConcreteSubject.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 *
 */
void testPattern(){
	LOGI("testPattern");
	//单例测试
	int val = Csingleton::getInstances()->add(2, 3);
	LOGI("singleton add = %d", val);
	//观察者测试
	VirObserver* p1 = new ConcreteObserverA();
	VirObserver* p2 = new ConcreteObserverB();
	VirSubject* subject = new ConcreteSubjectA();

	subject->Attach(p1);
	subject->Attach(p2);
	subject->Notify(1);
	subject->Detach(p1);
	subject->Notify(2);
	subject->Detach(p2);
	subject->Notify(3);

	delete subject;
	subject = NULL;
	delete p2;
	p2 = NULL;
	delete p1;
	p1 = NULL;
}

#ifdef __cplusplus
}
#endif
