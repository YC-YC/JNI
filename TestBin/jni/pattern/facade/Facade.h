/*
 * Facade.h
 *	外观模式
 *  Created on: 2018-5-3
 *      Author: YC2
 */

#ifndef FACADE_H_
#define FACADE_H_

#include "Log.h"
#include "comdef.h"

class SubSystemOne{
public:
	void method1(){
		LOGI("SubSystemOne method1");
	}
};
class SubSystemTwo{
public:
	void method2(){
		LOGI("SubSystemTwo method2");
	}
};
class SubSystemThree{
public:
	void method3(){
		LOGI("SubSystemThree method3");
	}
};
class SubSystemFour{
public:
	void method4(){
		LOGI("SubSystemFour method4");
	}
};

class Facade{
private:
	SubSystemOne* m_pSubSystemOne;
	SubSystemTwo* m_pSubSystemTwo;
	SubSystemThree* m_pSubSystemThree;
	SubSystemFour* m_pSubSystemFour;
public:
	Facade(){
		m_pSubSystemOne = new SubSystemOne();
		m_pSubSystemTwo = new SubSystemTwo();
		m_pSubSystemThree = new SubSystemThree();
		m_pSubSystemFour = new SubSystemFour();
	}
	~Facade(){
		delete m_pSubSystemOne;
		m_pSubSystemOne = NULL;
		delete m_pSubSystemTwo;
		m_pSubSystemTwo = NULL;
		delete m_pSubSystemThree;
		m_pSubSystemThree = NULL;
		delete m_pSubSystemFour;
		m_pSubSystemFour = NULL;

	}
	void methodA(){
		m_pSubSystemOne->method1();
		m_pSubSystemTwo->method2();
	}

	void methodB(){
		m_pSubSystemThree->method3();
		m_pSubSystemFour->method4();
	}

};

#endif /* FACADE_H_ */
