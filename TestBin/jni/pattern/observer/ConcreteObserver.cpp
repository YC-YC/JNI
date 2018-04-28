/*
 * ConcreteObserver.cpp
 *
 *  Created on: 2018-4-28
 *      Author: YC2
 */
#include "ConcreteObserver.h"
#include "Log.h"


ConcreteObserverA::ConcreteObserverA(){
	LOGI("ConcreteObserverA");
}
ConcreteObserverA::~ConcreteObserverA(){
	LOGI("~ConcreteObserverA");
}

void ConcreteObserverA::onNotify(int cmd){
	LOGI("ConcreteObserverA onNotify cmd = %d", cmd);
}


ConcreteObserverB::ConcreteObserverB(){
	LOGI("ConcreteObserverB");
}
ConcreteObserverB::~ConcreteObserverB(){
	LOGI("~ConcreteObserverB");
}

void ConcreteObserverB::onNotify(int cmd){
	VirObserver::onNotify(cmd);
	LOGI("ConcreteObserverB onNotify cmd = %d", cmd);
}
