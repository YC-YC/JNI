/*
 * Observer.h
 *	观察者模式
 *  Created on: 2018-4-28
 *      Author: YC2
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "comdef.h"
#include <list>

class VirObserver;

class VirSubject{
public:
	~VirSubject();
	virtual void Attach(VirObserver*);
	virtual void Detach(VirObserver*);
	void Notify(int);

protected:
	VirSubject();
private:
	typedef std::list<VirObserver *> OBSERVERLIST;
	OBSERVERLIST m_observerList;
};

class VirObserver{
public:
	~VirObserver();
	virtual void onNotify(int cmd);
protected:
	VirObserver();
private:

};

#endif /* OBSERVER_H_ */
