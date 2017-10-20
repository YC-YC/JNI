/*
 * CCarLink.h
 *
 *  Created on: 2017-9-16
 *      Author: YC2
 */

#ifndef CCARLINK_H_
#define CCARLINK_H_


#ifdef __cplusplus
extern "C" {
#endif

class CCarLink{
public:
	static int init(JavaVM *vm, JNIEnv *env);
	static int getRadioList(char* data);
	static int getBtMsg(char* data);
	static int getCanMsg(char* data);
	static bool putBtMsg(char* data, int length);
};


#ifdef __cplusplus
}
#endif

#endif /* CCARLINK_H_ */
