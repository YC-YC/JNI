/*
 * ShmFunc.h
 *
 *  Created on: 2018-5-23
 *      Author: YC2
 */

#ifndef SHM_FUNC_H_
#define SHM_FUNC_H_



//创建信号号
int createSemaphore(key_t key);
//获取信号量
bool getSemaphore(int semId);
//释放信号量
bool releaseSemaphore(int semId);
//删除信号量
bool deleteSemaphore(int semId);

//创建共享内存
int createShareMemory(key_t id, int size);
//获取共享内存
int getShareMemory(key_t id, int size);
//绑定共享内存
void* attachShareMemory(int shmId);
//解绑定
bool detachShareMemory(const void*shmaddr);
//删除共享内存
bool deleteShareMemory(int shmId);



#endif /* SHM_FUNC_H_ */
