/*
 * TestInterface.cpp
 *接口测试
 *  Created on: 2018-5-11
 *      Author: YC2
 */

#include "comdef.h"
#include "Log.h"
#include "Interface.h"

#ifdef __cplusplus
extern "C"
{
#endif

static void cb_studentInfo(STUDENT_INFO* info);
static void cb_teacherInfo(TEACHER_INFO* info);

static YCCB_STRUCT callbacks = {
	sizeof(YCCB_STRUCT),
	cb_studentInfo,
	cb_teacherInfo

};


void testInterface(){
	LOGI("testInterface");
	CB* cb = new CB();
	cb->registerCallback(&callbacks);
	cb->callback();
}

static void cb_studentInfo(STUDENT_INFO* info){
	LOGI("cb_studentInfo name=%s, age=%d", info->name, info->age);
}
static void cb_teacherInfo(TEACHER_INFO* info){
	LOGI("cb_studentInfo name=%s, age=%d", info->name, info->age);
}

#ifdef __cplusplus
}
#endif
