/*
 * Utils.h
 *
 *  Created on: 2016-1-20
 *      Author: YC
 */

#ifndef UTILS_H_
#define UTILS_H_
#include <iconv.h>

class Utils{
	static int code_convert(char* from_charset, char* toCharSet, char* inBuff, int inLen, char* outBuff, int outLen)
	{
		iconv_t cd;
		int rc;
		char ** pin = &inBuff;
		char ** pou = &outBuff;
		cd = iconv_open(toCharSet, from_charset);
		if (cd == 0)
		{
			return -1;
		}
		memset(outBuff, 0, outLen);
		if (iconv(cd, pin, &inLen, pou, &outLen) == -1)
		{
			return -1;
		}
		iconv_close(cd);
		return 0;
	}
};


#endif /* UTILS_H_ */
