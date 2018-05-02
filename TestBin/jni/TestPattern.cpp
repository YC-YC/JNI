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
#include "ICommand.h"
#include "Strategy.h"
#include "Decorator.h"

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

	//命令模式
	Receiver* pRece = new Receiver();
	Command* pCmdRice = new ConcreteCommandA(pRece);
	Command* pCmdNoodle = new ConcreteCommandB(pRece);
	Command* pCmdRice2 = new ConcreteCommandA(pRece);
	Command* pCmdNoodle2 = new ConcreteCommandB(pRece);
	Invoke* pInv = new Invoke();
	LOGI("Addcommand");
	pInv->addCommand(pCmdRice);
	pInv->addCommand(pCmdNoodle);
	pInv->addCommand(pCmdRice2);
	pInv->addCommand(pCmdNoodle2);
	pInv->sendCommand();

	LOGI("delete command");
	pInv->delCommand(pCmdNoodle);
	pInv->delCommand(pCmdRice2);
	pInv->sendCommand();

	LOGI("delete command");
	pInv->delCommand(pCmdNoodle2);
	pInv->delCommand(pCmdRice);
	pInv->sendCommand();

	//策略模式
	Character* pChar = new King();
	Weapon* pAK47 = new AK47();
	Weapon* pKnife = new Knife();

	pChar->fight();
	pChar->setWeapon(pAK47);
	pChar->fight();
	pChar->setWeapon(pKnife);
	pChar->fight();

	delete pAK47;
	pAK47 = NULL;
	delete pKnife;
	pKnife = NULL;

	//装饰者模式
	Phone* pPhone = new IPhone();
	pPhone->showPhone();
	DecoratorPhone* decorator = new DecoratorPhoneA(pPhone);
	decorator->showPhone();

	delete decorator;
	decorator = NULL;
	delete pPhone;
	pPhone = NULL;
}

#ifdef __cplusplus
}
#endif
