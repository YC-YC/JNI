/*
 * CSingleton.h
 *	单例模式
 *  Created on: 2018-4-16
 *      Author: YC2
 */

#ifndef CSINGLETON_H_
#define CSINGLETON_H_
#include "comdef.h"
class Csingleton{
public:
	static Csingleton* getInstances(){
		if (m_pInstance == NULL){
			m_pInstance = new Csingleton();
		}
		return m_pInstance;
	}
	~Csingleton(){
		if (m_pInstance != NULL){
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

	int add(int a, int b);
private:
	Csingleton(){

	}

private:
	static Csingleton* m_pInstance;
};

#endif /* CSINGLETON_H_ */
