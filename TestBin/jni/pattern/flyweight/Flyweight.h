/*
 * Flyweight.h
 *	享元模式（管理多个对象）
 *  Created on: 2018-5-6
 *      Author: Administrator
 */

#ifndef FLYWEIGHT_H_
#define FLYWEIGHT_H_
#include "Log.h"
#include <vector>
using namespace std;
class Flyweight{
public:
	~Flyweight(){}
	int getKey(){
		return this->key;
	}
protected:
	Flyweight(int key){
		this->key = key;
	}
private:
	int key;
};

class ConcreteFlyweight:public Flyweight{
public:
	ConcreteFlyweight(int key):Flyweight(key){}
	~ConcreteFlyweight(){}

};

class FlyweightFactory{
public:
	FlyweightFactory(){}
	~FlyweightFactory(){}

	Flyweight* getFlyWeight(int key){
		vector<Flyweight*>::iterator it = mFlyweights.begin();
		for(; it != mFlyweights.end(); it++){
			if ((*it)->getKey() == key){
				return *it;
			}
		}
		Flyweight* flyweight = new ConcreteFlyweight(key);
		mFlyweights.push_back(flyweight);
		return flyweight;
	}

	int getFlyweightCount(){
		return mFlyweights.size();
	}
private:
	vector<Flyweight*> mFlyweights;
};



#endif /* FLYWEIGHT_H_ */
