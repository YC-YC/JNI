/*
 * CustomFun.h
 *
 *  Created on: 2016-1-12
 *      Author: guoxs
 */

#ifndef _CUSTOM_FUN_H_
#define _CUSTOM_FUN_H_

#include "CommDef.h"

// 编码转换函数
bool CharsetConvert(const char *pFromCharset, const char *pToCharset,
		char *pIn, UINT inLen, char *pOut, UINT outLen);

bool WStringIsSame(const wchar_t *pWStr1, const wchar_t *pWStr2);

bool SaveDataToFile(const char *pData, UINT dataLen, const char *pSavePath);

#endif /* _CUSTOM_FUN_H_ */
