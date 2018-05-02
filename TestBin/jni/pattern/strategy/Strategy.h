/*
 * Strategy.h
 *	策略模式(实现几个策略的实现)
 *  Created on: 2018-5-2
 *      Author: YC2
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

#include "Log.h"
#include "comdef.h"

//抽象策略类
class Weapon{
public:
	virtual void useWeapon() = 0;
};

//策略类实现A
class AK47:public Weapon{
public:
	void useWeapon(){
		LOGI("use ak47");
	}
};

//策略类实现B
class Knife:public Weapon{
public:
	void useWeapon(){
		LOGI("use knife");
	}
};


class Character{
public:
	Character(){
		m_pWeapon = NULL;
	}
	void setWeapon(Weapon* pWeapon){
		m_pWeapon = pWeapon;
	}

	virtual void fight() = 0;
protected:
	Weapon* m_pWeapon;
};

class King:public Character{
public:
	void fight(){
		LOGI("King fight");
		if (this->m_pWeapon == NULL){
			LOGI("no weapon set");
		}
		else{
			this->m_pWeapon->useWeapon();
		}
	}
};

#endif /* STRATEGY_H_ */
