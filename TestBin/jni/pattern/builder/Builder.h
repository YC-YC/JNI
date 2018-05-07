/*
 * Builder.h
 *
 *  Created on: 2018-5-3
 *      Author: YC2
 */

#ifndef BUILDER_H_
#define BUILDER_H_
#include "Log.h"
#include "comdef.h"
#include <string>
using namespace std;
class Product{
public:
	Product(){}
	~Product(){}
	void setPartA(const string& s){
		this->m_PartA = s;
	}
	void setPartB(const string& s){
		this->m_PartB = s;
	}
private:
	string m_PartA;
	string m_PartB;
};



#endif /* BUILDER_H_ */
