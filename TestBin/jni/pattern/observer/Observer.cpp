/*
 * Subject.cpp
 *
 *  Created on: 2018-4-28
 *      Author: YC2
 */
#include "Observer.h"
#include "Log.h"
using namespace std;

VirSubject::VirSubject(){
	LOGI("VirSubject");
}

VirSubject::~VirSubject(){
	LOGI("~VirSubject");
}

void VirSubject::Attach(VirObserver* observer){
	LOGI("VirSubject::Attach");
	m_observerList.push_back(observer);
}

void VirSubject::Detach(VirObserver* observer){
	LOGI("VirSubject::Detach");
	list<VirObserver*>::iterator it = m_observerList.begin();
	while(it != m_observerList.end()){
		if ((*it) == observer){
			m_observerList.erase(it);
			break;
		}
		it++;
	}
}

void VirSubject::Notify(int cmd){
	LOGI("VirSubject::Notify cmd = %d", cmd);
	list<VirObserver*>::iterator it = m_observerList.begin();
		while(it != m_observerList.end()){
			(*it)->onNotify(cmd);
			it++;
		}
}
VirObserver::VirObserver(){
	LOGI("VirObserver");
}

void VirObserver::onNotify(int cmd){
	LOGI("VirObserver::onNotify cmd = %d", cmd);
}

VirObserver::~VirObserver(){
	LOGI("~VirObserver");
}
