/*
 * CS75SendHelper.h
 *
 *  Created on: 2017-11-6
 *      Author: YC2
 */

#ifndef CS75SENDHELPER_H_
#define CS75SENDHELPER_H_

#include "SendCanCmdManager.h"

#ifdef __cplusplus
extern "C" {
#endif

class CS75SendHelper{
public:
	static int FullSetCanData(int moduleId, unsigned char* buffer, int length);

	static int SetCanData(int moduleId, int index, int length, int what);

	static int GetFullCanData(int moduleId, unsigned char* buffer, int length);
};

#ifdef __cplusplus
}
#endif


#endif /* CS75SENDHELPER_H_ */
