/*
 * Mememto.h
 *	备忘录模式
 *  Created on: 2018-5-6
 *      Author: Administrator
 */

#ifndef MEMEMTO_H_
#define MEMEMTO_H_

#include "Log.h"
#include "comdef.h"

//保存Originator需要保存的数据，声明Originato为友元类，对其它类不提供public方法
class Mememto{
	friend class Originator;	//声明Originator可以访问稀有成员
public:
	Mememto(int state){
		this->state = state;
	}
	~Mememto(){}

private:
	int state;
};

//添加获取和恢复Mememto实例的方法
class Originator{
public:
	Originator(int state){
		this->state = state;
	}
	~Originator(){}

	Mememto* createMememto(){
		return new Mememto(state);
	}

	void restoreToMememto(Mememto* pMememto){
		LOGI("original restoreToMememto");
		this->state = pMememto->state;
		delete pMememto;
		pMememto = NULL;
	}

	void setState(int state){
		LOGI("original set new state = %d", state);
		this->state = state;
	}

	int getState(){
		return this->state;
	}
private:
	int state;
};

//用以保存Mememto对象
class Taker{
public:
	Taker(){}
	~Taker(){}
	void setMememto(Mememto* pMememto){
		LOGI("Taker save Mememto");
		m_pMememto = pMememto;
	}

	Mememto* getMememto(){
		return m_pMememto;
	}
private:
	Mememto* m_pMememto;
};


#endif /* MEMEMTO_H_ */
