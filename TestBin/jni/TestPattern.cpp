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
#include "Proxy.h"
#include "Facade.h"
#include "Template.h"
#include "Adapter.h"
#include "Mediator.h"
#include "Mememto.h"
#include "Flyweight.h"
#include "Component.h"
#include "Bridge.h"
#include "Prototype.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 *
 */
void testPattern(){
	LOGI("testPattern");
	LOGI("\n---------单例模式-----------\n");
	int val = Csingleton::getInstances()->add(2, 3);
	LOGI("singleton add = %d", val);

	LOGI("\n---------观察者模式-----------\n");
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

	LOGI("\n---------命令模式-----------\n");
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

	LOGI("\n---------策略模式-----------\n");
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

	LOGI("\n---------装饰者模式-----------\n");
	Phone* pPhone = new IPhone();
	pPhone->showPhone();
	DecoratorPhone* decorator = new DecoratorPhoneA(pPhone);
	decorator->showPhone();

	delete decorator;
	decorator = NULL;
	delete pPhone;
	pPhone = NULL;

	LOGI("\n---------代理模式-----------\n");
	Proxy* pProxy = new Proxy();
	pProxy->request();
	delete pProxy;
	pProxy = NULL;

	LOGI("\n---------外观模式-----------\n");
	Facade* pFacade = new Facade();
	pFacade->methodA();
	pFacade->methodB();
	delete pFacade;
	pFacade = NULL;

	LOGI("\n---------模块模式-----------\n");
	AbstractTemplate* pTemplate = new ConcreteTemplateA();
	pTemplate->templateMethod();
	delete pTemplate;
	pTemplate = new ConcreteTemplateB();
	pTemplate->templateMethod();
	delete pTemplate;

	LOGI("\n---------适配模式-----------\n");

	LOGI("\n---------类适配模式-----------\n");
	Target* target = new Adapter();
	target->Request();

	LOGI("\n---------对象适配模式-----------\n");
	Adaptee* adaptee = new Adaptee();
	target = new Adapter1(adaptee);
	target->Request();
	target = new Adapter1();
	target->Request();

	LOGI("\n---------中介模式-----------\n");
	ConcreteMediator* pMediator = new ConcreteMediator();

	Colleage* pColleageA = new ConcreteColleageA(pMediator);
	Colleage* pColleageB = new ConcreteColleageB(pMediator);

	pMediator->setColleageA(pColleageA);
	pMediator->setColleageB(pColleageB);

	pMediator->sendMsg(1, pColleageA);
	pMediator->sendMsg(2, pColleageB);

	LOGI("\n---------备忘录模式-----------\n");
	Originator* pOriginator = new Originator(5);
	int state = pOriginator->getState();
	LOGI("original current state = %d", state);

	Taker* pTaker = new Taker();
	pTaker->setMememto(pOriginator->createMememto());

	pOriginator->setState(10);
	state = pOriginator->getState();
	LOGI("original current state = %d", state);

	pOriginator->restoreToMememto(pTaker->getMememto());

	state = pOriginator->getState();
	LOGI("original current state = %d", state);

	LOGI("\n---------享元模式-----------\n");
	FlyweightFactory* pFactor = new FlyweightFactory();

	Flyweight* flyweight = pFactor->getFlyWeight(5);
	int key = flyweight->getKey();
	LOGI("Flyweight getKey = %d", key);

	flyweight = pFactor->getFlyWeight(10);
	key = flyweight->getKey();
	LOGI("Flyweight getKey = %d", key);

	LOGI("FlyweightFactory getFlyweightCount = %d", pFactor->getFlyweightCount());

	LOGI("\n---------组件模式-----------\n");
	Tree* pTree = new Tree();
	pTree->add(new Leaf());
	pTree->action();

	Component* leaf1 = new Leaf();
	Component* leaf2 = new Leaf();
	Tree* pTree2 = new Tree();
	pTree2->add(leaf1);
	pTree2->add(leaf2);
	pTree2->action();

	pTree->add(pTree2);
	pTree2->action();

	LOGI("\n---------桥接模式-----------\n");
	Implement* pImpl1 = new ConcreteImplememtA();
	Implement* pImpl2 = new ConcreteImplememtB();

	Abstraction* pAbst = new ConcreteAbstractionA(pImpl1);
	pAbst->action();
	pAbst = new ConcreteAbstractionA(pImpl2);
	pAbst->action();

	pAbst = new ConcreteAbstractionB(pImpl1);
	pAbst->action();
	pAbst = new ConcreteAbstractionB(pImpl2);
	pAbst->action();

	LOGI("\n---------桥接模式-----------\n");
	Prototype* pPrototype1 = new ConcretePrototypeA();
	Prototype* pPrototype2 = pPrototype1->Clone();

	Prototype* pPrototype3 = new ConcretePrototypeB();
	Prototype* pPrototype4 = pPrototype3->Clone();


}

#ifdef __cplusplus
}
#endif
