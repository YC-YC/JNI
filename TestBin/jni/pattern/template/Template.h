/*
 * Template.h
 *	模板模式：封装执行方法
 *  Created on: 2018-5-4
 *      Author: YC2
 */

#include "Log.h"
#include "comdef.h"

class AbstractTemplate{
public:
	virtual void method1() = 0;
	virtual void method2() = 0;
	void templateMethod(){
		method1();
		method2();
	}
};

class ConcreteTemplateA:public AbstractTemplate{
public:
	void method1(){
		LOGI("ConcreteTemplateA method1");
	}

	void method2(){
		LOGI("ConcreteTemplateA method2");
	}
};

class ConcreteTemplateB:public AbstractTemplate{
public:
	void method1(){
		LOGI("ConcreteTemplateB method1");
	}

	void method2(){
		LOGI("ConcreteTemplateB method2");
	}
};
