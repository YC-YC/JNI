/*
 * Decorator.h
 *	装饰者
 *  Created on: 2018-5-2
 *      Author: YC2
 */

#ifndef DECORATOR_H_
#define DECORATOR_H_
#include "Log.h"

class Phone{
public:
	virtual void showPhone() = 0;
};

class IPhone:public Phone{
	void showPhone(){
		LOGI("IPhone showPhone");
	}
};

class NokiaPhone:public Phone{
	void showPhone(){
		LOGI("Nokia showPhone");
	}
};

class DecoratorPhone: public Phone{
private:
	Phone* m_pPhone;
public:
	DecoratorPhone(Phone* pPhone):m_pPhone(pPhone){}
	virtual void showPhone(){
		m_pPhone->showPhone();
	}
};

class DecoratorPhoneA:public DecoratorPhone{
private:
	void addDecoratorBefor(){
		LOGI("DecoratorPhoneA addDecoratorBefor");
	}
	void addDecoratorAfter(){
		LOGI("DecoratorPhoneA addDecoratorAfter");
	}

public:
	DecoratorPhoneA(Phone* pPhone):DecoratorPhone(pPhone){}

	void showPhone(){
		addDecoratorBefor();
		DecoratorPhone::showPhone();	//调用父类方法
		addDecoratorAfter();
	}

};

#endif /* DECORATOR_H_ */
