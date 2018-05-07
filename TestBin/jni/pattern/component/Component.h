/*
 * Component.h
 *
 *  Created on: 2018-5-7
 *      Author: Administrator
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_
#include "Log.h"
#include "comdef.h"
#include <vector>
using namespace std;
class Component {
public:
	virtual ~Component() {
	}
	virtual void action() = 0;
	virtual void add(Component* pCom) {
		LOGI("Component add");
	}
	virtual void remove(Component* pCom) {
		LOGI("Component remove");
	}
	virtual Component* getChild(int index) {
		LOGI("Component getChild index = %d", index);
		return NULL;
	}
protected:
	Component() {
	}
};

class Leaf: public Component {
public:
	Leaf() {
	}
	~Leaf() {
	}
	void action() {
		LOGI("Leaf action");
	}
};

class Tree: public Component {
public:
	Tree() {
	}
	~Tree() {
	}
	void action() {
		LOGI("Tree action");
		vector<Component*>::iterator it = mComponents.begin();
		for (; it != mComponents.end(); it++) {
			(*it)->action();
		}
	}
	virtual void add(Component* pCom) {
		LOGI("Tree add");
		mComponents.push_back(pCom);
	}
	virtual void remove(Component* pCom) {
		LOGI("Tree remove");
		vector<Component*>::iterator it = mComponents.begin();
		for (; it != mComponents.end(); it++) {
			if (*it == pCom) {
				mComponents.erase(it);
				break;
			}
		}
	}
	virtual Component* getChild(int index) {
		LOGI("Tree getChild index = %d", index);
		if (index < 0 || index > mComponents.size()) {
			return NULL;
		}
		return mComponents[index];
	}
private:
	vector<Component*> mComponents;
};

#endif /* COMPONENT_H_ */
