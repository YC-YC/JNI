/*
 * CS75SendHelper.cpp
 *
 *  Created on: 2017-11-6
 *      Author: YC2
 */

#include "CS75SendHelper.h"

SendCanCmdManager gSendCanCmdManager;

int CS75SendHelper::FullSetCanData(int moduleId, unsigned char* buffer, int length){
	return gSendCanCmdManager.defaultCanData(moduleId, buffer, length);
}

int CS75SendHelper::SetCanData(int moduleId, int index, int length, int what){
	return gSendCanCmdManager.setCanData(moduleId, index, length, what);
}

int CS75SendHelper::GetFullCanData(int moduleId, unsigned char* buffer, int length){
	return gSendCanCmdManager.getCanData(moduleId, buffer, length);
}


