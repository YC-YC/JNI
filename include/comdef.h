/*
 * comdef.h
 *
 *  Created on: 2016-1-12
 *      Author: YC
 */

#ifndef COMDEF_H_
#define COMDEF_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/times.h>
#include <pthread.h>
#include "Log.h"

//using namespace std;


typedef unsigned short int 		 WORD;
typedef char                     CHAR;
typedef unsigned char            BYTE;
typedef unsigned int             DWORD;
typedef float                    REAL;
typedef float                    FLOAT;
typedef double                   DOUBLE;
typedef int                      INT;
typedef long                     LONG;
typedef BYTE  *                  LPBYTE;
typedef WORD  *                  LPWORD;
typedef DWORD  *                 LPDWORD;
typedef long long                LONG64;
typedef long long                LONGLONG;
typedef DWORD                    UINT;
typedef void *                   LPVOID;
typedef DWORD                    HRESULT;
typedef const char*				 CPCHAR;

typedef pthread_mutex_t CRITICAL_SECTION;

inline void InitializeCriticalSection(void *pSection)
{
	pthread_mutex_init((CRITICAL_SECTION*)pSection, NULL);
}
inline void DeleteCriticalSection(void *pSection)
{
	pthread_mutex_destroy((CRITICAL_SECTION*)pSection);
}
inline void EnterCriticalSection(void *pSection)
{
	pthread_mutex_lock((CRITICAL_SECTION*)pSection);
}
inline void LeaveCriticalSection(void *pSection)
{
	pthread_mutex_unlock((CRITICAL_SECTION*)pSection);
}
inline void CopyMemory(LPVOID pTarget,const void* pSource,DWORD copyByte)
{
	memcpy(pTarget,pSource,copyByte);
}
inline void ZeroMemory(LPVOID pTarget,DWORD  zeroByte)
{
	memset(pTarget,0, zeroByte);
}
#define Sleep(x) usleep(1000*x);

inline DWORD GetTickCount()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((DWORD)(ts.tv_sec*1000 + ts.tv_nsec/(1000*1000)));
}

#define MAX_PATH		256

#define BIT0	((BYTE)(1<<0))
#define BIT1	((BYTE)(1<<1))
#define BIT2	((BYTE)(1<<2))
#define BIT3	((BYTE)(1<<3))
#define BIT4	((BYTE)(1<<4))
#define BIT5	((BYTE)(1<<5))
#define BIT6	((BYTE)(1<<6))
#define BIT7	((BYTE)(1<<7))

#define BIT8	((WORD)(1<<8))
#define BIT9	((WORD)(1<<9))
#define BIT10	((WORD)(1<<10))
#define BIT11	((WORD)(1<<11))
#define BIT12	((WORD)(1<<12))
#define BIT13	((WORD)(1<<13))
#define BIT14	((WORD)(1<<14))
#define BIT15	((WORD)(1<<15))

#define getSize(x)	(sizeof(x)/x##[0])

#endif /* COMDEF_H_ */
