/*
 * TestStd.cpp
 *C++ std库测试
 *  Created on: 2018-5-8
 *      Author: YC2
 */

#include "comdef.h"
#include <list>
#include <vector>
#include <queue>
#include <map>
#include<algorithm>

using namespace std;
#ifdef __cplusplus
extern "C"
{
#endif
typedef list<int> LIST_INT;	//定义list类型
typedef vector<int> VEC_INT;	//定义Vector类型
typedef deque<int> QUE_INT;	//定义deque类型
typedef map<int, int> MAP_INT_INT;	//定义map类型
/**
 *
 */
void testStd(){
	LOGI("testStd");
	LOGI("\n---------list-----------\n");
	LIST_INT mList;
	LIST_INT mList2(5);//含有5个元素的list
	LOGI("list count = %d", mList.size());
	LIST_INT mList3(3, 2);
	LIST_INT mList4(mList2);//用list2初始化list
	LIST_INT mList5(mList2.begin(), mList2.end());//同list4

	LIST_INT listOne;
	listOne.push_front(2);
	listOne.push_front(3);
	listOne.push_back(1);

	LIST_INT::iterator it;
	for(it = listOne.begin(); it != listOne.end(); it++){
		LOGI("list listOne = %d", *it);
	}

	LIST_INT::reverse_iterator rIt;
	for(rIt = listOne.rbegin(); rIt != listOne.rend(); rIt++){
		LOGI("revert list listOne = %d", *rIt);
	}

	size_t maxSize = listOne.max_size();
	LOGI("list maxSize = %d", maxSize);

	listOne.push_back(2);
	listOne.push_back(3);
	for(it = listOne.begin(); it != listOne.end(); it++){
		LOGI("Befor unique, list listOne = %d", *it);
	}
	listOne.unique();
	for(it = listOne.begin(); it != listOne.end(); it++){
		LOGI("After unique,  list listOne = %d", *it);
	}

	listOne.insert(listOne.begin(), 9);	//插入
	for(it = listOne.begin(); it != listOne.end(); it++){
		LOGI("After insert,  list listOne = %d", *it);
	}
	listOne.sort();	//排序
	for(it = listOne.begin(); it != listOne.end(); it++){
		LOGI("After sort,  list listOne = %d", *it);
	}
	listOne.erase(listOne.begin());
	for(it = listOne.begin(); it != listOne.end(); it++){
		LOGI("After erase,  list listOne = %d", *it);
	}

	LOGI("\n---------vector-----------\n");
	VEC_INT vecOne;
	vecOne.push_back(5);
	vecOne.push_back(6);
	//获取值
	int val = vecOne[0];
	val = vecOne.at(0);
	vecOne.insert(vecOne.begin()+1, 4);	//在第二个元素前插入

	LOGI("\n---------deque-----------\n");
	QUE_INT queOne;
	queOne.push_back(2);
	queOne.push_front(1);
	queOne.insert(queOne.begin(), 1);
	queOne.front();
	queOne.back();
	queOne.pop_back();
	queOne.pop_front();

	LOGI("\n---------map-----------\n");

	MAP_INT_INT mapOne;
	mapOne.insert(pair<int, int>(1, 100));
	//mapOne.insert(2, 200);
	mapOne[2] = 300;	//数组形式插入
	MAP_INT_INT::iterator mIt;
	for(mIt = mapOne.begin(); mIt != mapOne.end(); mIt++){
		LOGI("list map = %d", *mIt);
	}
	mIt = mapOne.find(1);
	if(mIt == mapOne.end()){
		LOGI("find No Data");
	}
	else{
		LOGI("find data first= %d, second =%d", mIt->first, mIt->second);
	}


}

#ifdef __cplusplus
}
#endif
