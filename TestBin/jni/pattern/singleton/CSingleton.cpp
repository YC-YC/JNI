/*
 * CSingleton.cpp
 *
 *  Created on: 2018-4-16
 *      Author: YC2
 */

#include "CSingleton.h"

Csingleton* Csingleton::m_pInstance = NULL;

int Csingleton::add(int a, int b){
	return a+b;
}


