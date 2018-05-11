/*
 * Interface.h
 *	test interface
 *  Created on: 2018-5-11
 *      Author: YC2
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <stdio.h>
#include <string.h>

typedef struct{
	char name[10];
	int age;
}STUDENT_INFO;

typedef struct{
	char name[10];
	int age;
}TEACHER_INFO;

typedef void(*YCCB_studentInfo)(STUDENT_INFO* info);
typedef void(*YCCB_teacherInfo)(TEACHER_INFO* info);

typedef struct{
	int size;
	YCCB_studentInfo student_info_cb;
	YCCB_teacherInfo teacher_info_cb;
}YCCB_STRUCT;

class CB{
public:
	CB(){}
	~CB(){}
	void registerCallback(YCCB_STRUCT* yccb){
		mYCCB = yccb;
	}

	void callback(){
		STUDENT_INFO student = {"student", 20};
		TEACHER_INFO teacher = {"teacher", 40};
		if(mYCCB != NULL){
			mYCCB->student_info_cb(&student);
			mYCCB->teacher_info_cb(&teacher);
		}
	}
private:
	YCCB_STRUCT* mYCCB;
};


#endif /* INTERFACE_H_ */
