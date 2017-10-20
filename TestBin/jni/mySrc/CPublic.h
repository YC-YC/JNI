/*
 * CPublic.h
 *
 *  Created on: 2017-9-16
 *      Author: YC2
 */

#ifndef CPUBLIC_H_
#define CPUBLIC_H_

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

class CPublic{
public:
	static int getEnv(JavaVM *pVm, JNIEnv **envnow);

	static void detachEnv(JavaVM *pVm, int type);
};

#ifdef __cplusplus
}
#endif

#endif /* CPUBLIC_H_ */
