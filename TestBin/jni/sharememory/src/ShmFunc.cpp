/*
 * ShmFunc.c
 *
 *  Created on: 2018-5-23
 *      Author: YC2
 */

#include "ShmFunc.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>

#ifdef __cplusplus
extern "C"
{
#endif

//创建信号号
int createSemaphore(key_t key){
	return semget(key, 1, 0666|IPC_CREAT);
}
//获取信号量
bool getSemaphore(int semId){
	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_op = 1;
	sb.sem_flg = 0;
	return semop(semId, &sb, 1) != -1;
}
//释放信号量
bool releaseSemaphore(int semId){
	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_op = -1;
	sb.sem_flg = 0;
	return semop(semId, &sb, 1) != -1;
}
//删除信号量
bool deleteSemaphore(int semId){
	return semctl(semId, 0, IPC_RMID, NULL) != -1;
}

//创建共享内存
int createShareMemory(key_t id, int size){
	return shmget(id, size, 0666|IPC_CREAT);
}
//获取共享内存
int getShareMemory(key_t id, int size){
	return shmget(id, size, 0);
}
//绑定共享内存
void* attachShareMemory(int shmId){
	return shmat(shmId, 0, 0);
}
//解绑定
bool detachShareMemory(const void*shmaddr){
	return (shmdt(shmaddr) != -1);
}
//删除共享内存
bool deleteShareMemory(int shmId){
	return (shmctl(shmId, IPC_RMID, 0)==-1);
}


#ifdef __cplusplus
}
#endif
