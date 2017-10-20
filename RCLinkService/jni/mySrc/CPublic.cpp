/*
 * CPublic.cpp
 *
 *  Created on: 2017-9-16
 *      Author: YC2
 */
#include "CPublic.h"
#include <stdio.h>

int CPublic::getEnv(JavaVM *pVm, JNIEnv **envnow)
{
	int status, type;

    type = 0;
    status = pVm->GetEnv((void **)envnow, JNI_VERSION_1_6);
    if(status >= 0) {
    	type = 1;
    	printf("CPublic getEnv type 1");
    	return type;
    }

    status = pVm->AttachCurrentThread(envnow, NULL);
    if(status >= 0) {
    	type = 2;
    }

    return type;
}

void CPublic::detachEnv(JavaVM *pVm, int type)
{
	if(type == 2) {
        pVm->DetachCurrentThread();
    }
}

