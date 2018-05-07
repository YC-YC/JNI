/*
 * Prototype.h
 *
 *  Created on: 2018-5-8
 *      Author: Administrator
 */

#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_
#include "Log.h"

class Prototype {
public:
	virtual ~Prototype() {
		LOGI("~Prototype");
	}
	virtual Prototype* Clone() = 0;
protected:
	Prototype() {
		LOGI("Prototype");
	}
};

class ConcretePrototypeA: public Prototype {
public:
	~ConcretePrototypeA() {
		LOGI("~ConcretePrototypeA");
	}
	Prototype* Clone() {
		return new ConcretePrototypeA(*this);
	}
	ConcretePrototypeA() {
		LOGI("ConcretePrototypeA");
	}
	ConcretePrototypeA(const ConcretePrototypeA& conPt) {
		LOGI("ConcretePrototypeA with param");
	}
};

class ConcretePrototypeB: public Prototype {
public:
	~ConcretePrototypeB() {
		LOGI("~ConcretePrototypeB");
	}
	Prototype* Clone() {
		return new ConcretePrototypeB(*this);
	}
	ConcretePrototypeB() {
		LOGI("ConcretePrototypeB");
	}
	ConcretePrototypeB(const ConcretePrototypeB& conPt) {
		LOGI("ConcretePrototypeB with param");
	}
};

#endif /* PROTOTYPE_H_ */
