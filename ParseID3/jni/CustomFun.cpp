/*
 * CustomFun.cpp
 *
 *  Created on: 2016-1-12
 *      Author: guoxs
 */

#include <stdio.h>
#include <iconv.h>

#include "CustomFun.h"

bool CharsetConvert(const char *pFromCharset, const char *pToCharset,
		char *pIn, UINT inLen, char *pOut, UINT outLen) {
	iconv_t icd;

	if ((iconv_t)-1 == (icd = iconv_open(pToCharset, pFromCharset))) {
		return false;
	}

	if ((unsigned int)-1 == iconv(icd, &pIn, &inLen, &pOut, &outLen)) {
		iconv_close(icd);
		return false;
	}

	iconv_close(icd);

	return true;
}

bool WStringIsSame(const wchar_t *pWStr1, const wchar_t *pWStr2) {
	if ((pWStr1 == NULL) && (pWStr2 == NULL)) {
		return true;
	} else if ((pWStr1 == NULL) || (pWStr2 == NULL)) {
		return false;
	}

	int i = 0;
	while ((pWStr1[i] != 0) && (pWStr2[i] != 0)) {
		if (pWStr1[i] != pWStr2[i]) {
			return false;
		}
		++i;
	}

	if ((pWStr1[i] == 0) && (pWStr2[i] == 0)) {
		return true;
	}

	return false;
}

bool SaveDataToFile(const char *pData, UINT dataLen, const char *pSavePath) {
	if ((pData == NULL) || (dataLen == 0) || (pSavePath == NULL)) {
		return false;
	}

	FILE *pFile = fopen(pSavePath, "wb");
	if (pFile == NULL) {
		return false;
	}

	const UINT oneMB = 1024 * 1024;		// 一次性最多写1M
	while (dataLen != 0) {
		if (dataLen > oneMB) {
			if (!fwrite(pData, oneMB, 1, pFile)) {
				break;
			}
			dataLen -= oneMB;
		} else {
			if (!fwrite(pData, dataLen, 1, pFile)) {
				break;
			}
			dataLen = 0;
		}
	}

	fclose(pFile);

	return (dataLen == 0);
}
