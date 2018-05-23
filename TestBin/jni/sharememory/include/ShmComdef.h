/*
 * ShmComdef.h
 *
 *  Created on: 2018-5-23
 *      Author: YC2
 */

#ifndef SHM_COMDEF_H_
#define SHM_COMDEF_H_

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MEMORY_KEY_ID	0x8187
#define DATA_LEN	255

typedef struct{
	int cmd;
	char data[DATA_LEN+1];
}Data_st;

typedef struct
{
	int semId;
	Data_st shmData;

}SHAREDATA;


#endif /* SHM_COMDEF_H_ */
