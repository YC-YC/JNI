/*
 * CommDef.h
 *
 *  Created on: 2016-1-11
 *      Author: guoxs
 */

#ifndef _COMMDEF_H_
#define _COMMDEF_H_

#define ID3_ITEM_LEN	128

#define Min(x, y)		((x < y)? x: y)


typedef unsigned char	BYTE;
typedef unsigned int	UINT;

typedef struct {
	char title[ID3_ITEM_LEN + 1];		// 曲目
	char artist[ID3_ITEM_LEN + 1];		// 作者
	char album[ID3_ITEM_LEN + 1];		// 专辑
	char year[ID3_ITEM_LEN + 1];		// 年份
	char comment[ID3_ITEM_LEN + 1];		// 备注
} S_ID3_INFO;

// 图片数据信息
typedef struct {
	BYTE *pData;
	UINT dataLen;
} S_PIC_INFO;

#endif /* _COMMDEF_H_ */
