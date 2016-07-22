/*
 * WMAID3Parser.cpp
 *
 *  Created on: 2016-1-11
 *      Author: guoxs
 */

#include <iostream>

#include "WMAID3Parser.h"
#include "CustomFun.h"
#include "Debug.h"


#define WMA_HEAD_INFO_SIZE		30
#define WMA_FRAME_INFO_SIZE		24
#define WMA_FRAME_FLAG_SIZE		16

#define WM_ALBUMTITLE			L"WM/AlbumTitle"
#define WM_YEAR					L"WM/Year"
#define WM_PICTURE				L"WM/Picture"


// 定义WMA文件头常量标识
static const S_WMA_HEAD_FLAG WMA_HEAD_FLAGCONST = {
	0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
	0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
};

// 定义WMA标准帧及扩展帧常量标识
static const S_WMA_FRAME_HEAD_FLAG WMA_FRAMEHEAD_STANDARD = {
	0x33, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
	0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
};

static const S_WMA_FRAME_HEAD_FLAG WMA_FRAMEHEAD_EXTEND = {
	0x40, 0xA4, 0xD0, 0xD2, 0x07, 0xE3, 0xD2, 0x11,
	0x97, 0xF0, 0x00, 0xA0, 0xC9, 0x5E, 0xA8, 0x50
};


bool CWMAID3Parser::HandleParseID3(FILE *pWMAFile, S_ID3_INFO *pID3Info) {
	if (fseek(pWMAFile, 0, SEEK_SET)) {
		return false;
	}

	LOGICTRL(UART_DEBUG, "CWMAID3Parser::HandleParseID3++++++++++");

	S_WMA_HEAD_INFO headInfo = { 0 };     // 存放头信息
	if (!fread(&headInfo, WMA_HEAD_INFO_SIZE, 1, pWMAFile)) {
		return false;
	}

	// 判断是否WMA文件
	if (!BeWMAFile(headInfo.headFlag)) {
		return false;
	}

	LOGICTRL(UART_DEBUG, "Is WMAFile\n");

	// 计算要读取帧数据的字节数
	UINT frameDataSize = GetHeadSize(headInfo.headSize) - WMA_HEAD_INFO_SIZE;
	BYTE *pFrameData = new BYTE[frameDataSize];
	bool result = false;

	memset(pFrameData, 0, frameDataSize);
	if (fread(pFrameData, frameDataSize, 1, pWMAFile)) {
		// 解析帧数据
		result = ParseFrameData(pFrameData, frameDataSize, headInfo.headCount, pID3Info, NULL);
	}

	delete[] pFrameData;

	LOGICTRL(UART_DEBUG, "CWMAID3Parser::HandleParseID3----------");

	return result;
}

bool CWMAID3Parser::HandleParseID3Pic(FILE *pWMAFile, S_PIC_INFO *pPicInfo) {
	if (fseek(pWMAFile, 0, SEEK_SET)) {
		return false;
	}

	LOGICTRL(UART_DEBUG, "CWMAID3Parser::HandleParseID3Pic++++++++++");

	S_WMA_HEAD_INFO headInfo = { 0 };     // 存放头信息
	if (!fread(&headInfo, WMA_HEAD_INFO_SIZE, 1, pWMAFile)) {
		return false;
	}

	// 判断是否WMA文件
	if (!BeWMAFile(headInfo.headFlag)) {
		return false;
	}

	// 计算要读取帧数据的字节数
	UINT frameDataSize = GetHeadSize(headInfo.headSize) - WMA_HEAD_INFO_SIZE;
	BYTE *pFrameData = new BYTE[frameDataSize];
	bool result = false;

	memset(pFrameData, 0, frameDataSize);
	if (fread(pFrameData, frameDataSize, 1, pWMAFile)) {
		// 解析帧数据
		result = ParseFrameData(pFrameData, frameDataSize, headInfo.headCount, NULL, pPicInfo);
	}

	delete[] pFrameData;

	LOGICTRL(UART_DEBUG, "CWMAID3Parser::HandleParseID3Pic----------");

	return result;
}

bool CWMAID3Parser::BeWMAFile(const S_WMA_HEAD_FLAG &headFlag) {
	for (UINT i = 0; i < WMA_FRAME_FLAG_SIZE; ++i) {
		if (headFlag.flag[i] != WMA_HEAD_FLAGCONST.flag[i]) {
			return false;
		}
	}

	return true;
}

UINT CWMAID3Parser::GetHeadSize(const S_WMA_HEAD_SIZE &headSize) {
	return (UINT)((headSize.size[3]<<24) | (headSize.size[2]<<16) |
				  (headSize.size[1]<<8) | headSize.size[0]);
}

UINT CWMAID3Parser::GetFrameSize(const S_WMA_FRAME_HEAD_SIZE &frameSize) {
	return (UINT)((frameSize.size[3]<<24) | (frameSize.size[2]<<16) |
				  (frameSize.size[1]<<8) | frameSize.size[0]);
}

WMA_FRAMESTYLE_T CWMAID3Parser::GetFrameStyle(const S_WMA_FRAME_HEAD_FLAG &frameFlag) {
	// 判断是否标准帧
	if (BeSameFrameFlag(frameFlag, WMA_FRAMEHEAD_STANDARD))	{
		return WMA_FRAMESTYLE_STANDARD;
	}

	// 判断是否扩展帧
	if (BeSameFrameFlag(frameFlag, WMA_FRAMEHEAD_EXTEND)) {
		return WMA_FRAMESTYLE_EXTEND;
	}

	// 返回位置帧
	return WMA_FRAMESTYLE_UNKNOWN;
}

bool CWMAID3Parser::BeSameFrameFlag(const S_WMA_FRAME_HEAD_FLAG &firstFlag,
		const S_WMA_FRAME_HEAD_FLAG &secondFlag) {
	for (int i = 0; i < 16; ++i) {
		if (firstFlag.flag[i] != secondFlag.flag[i]) {
			return false;
		}
	}

	return true;
}

UINT CWMAID3Parser::CalUInt16Val(const BYTE *pByteBuf, int bufSize) {
	if ((pByteBuf == NULL) || (bufSize < 2)) {
		return 0;
	}

	return ((pByteBuf[1]<<8) | pByteBuf[0]);
}

UINT CWMAID3Parser::CalUInt32Val(const BYTE *pByteBuf, int bufSize) {
	if ((pByteBuf == NULL) || (bufSize < 4)) {
		return 0;
	}

	return ((pByteBuf[3]<<24) | (pByteBuf[2]<<16) | (pByteBuf[1]<<8) | pByteBuf[0]);
}

bool CWMAID3Parser::ParseFrameData(const BYTE *pFrameData, UINT dataLen, int frameNum,
		S_ID3_INFO *pID3Info, S_PIC_INFO *pPicInfo) {
	S_WMA_FRAME_HEAD_INFO frameHead;
	WMA_FRAMESTYLE_T frameStyle = WMA_FRAMESTYLE_UNKNOWN;
	UINT frameSize = 0;
	UINT pos = 0;
	bool result = false;

	LOGICTRL(UART_DEBUG, "ParseFrameData dataLen = %d, frameNum = %d\n", dataLen, frameNum);

	for (int i = 0; i < frameNum; ++i) {
		if (pos+24 >= dataLen) {
			break;
		}

		// 得到帧头失败
		if (!GetFrameHeadInfo(pFrameData+pos, dataLen-pos, frameHead)) {
			break;
		}

		// 得到帧风格类型
		frameStyle = GetFrameStyle(frameHead.frameFlag);

		// 是正确风格，取得帧大小
		frameSize = GetFrameSize(frameHead.frameSize);

		LOGICTRL(UART_DEBUG, "frameStyle = %d, frameSize = %d\n", frameStyle, frameSize);

		// 取得帧体内容
		if ((frameSize >= 24) && (pos+frameSize <= dataLen)) {
			// 是标准帧，解析标准帧
			if (frameStyle == WMA_FRAMESTYLE_STANDARD) {
				if (ParseStandardFrame(pFrameData+pos+24, frameSize-24, pID3Info)) {
					result = true;
				}
			} else if (frameStyle == WMA_FRAMESTYLE_EXTEND)	{	// 是扩展帧
				if (ParseExtendFrame(pFrameData+pos+24, frameSize-24, pID3Info, pPicInfo)) {
					result = true;
				}
			}

			pos += frameSize;
		} else {
			++pos;
		}
	}

	return result;
}

bool CWMAID3Parser::GetFrameHeadInfo(const BYTE *pFrameData, UINT dataLen, S_WMA_FRAME_HEAD_INFO &frameHead) {
	if ((pFrameData == NULL) || (dataLen < 24)) {
		return false;
	}

	// 得到帧标识
	int i = 0;
	for (i = 0; i < 16; ++i) {
		frameHead.frameFlag.flag[i] = pFrameData[i];
	}

	// 得到帧大小
	for (i = 0; i < 8; ++i) {
		frameHead.frameSize.size[i] = pFrameData[i+16];
	}

	return true;
}

bool CWMAID3Parser::ParseStandardFrame(const BYTE *pItemFrameData, UINT frameSize, S_ID3_INFO *pID3Info) {
	if (pID3Info == NULL) {
		return false;
	}

	LOGICTRL(UART_DEBUG, "ParseStandardFrame frameSize = %d\n", frameSize);

	// 计算标题信息大小
	UINT titleSize = CalUInt16Val(pItemFrameData, 2);

	// 计算艺术家信息大小
	UINT artistSize = CalUInt16Val(pItemFrameData+2, 2);

	// 计算版权信息大小
	UINT copyRightSize = CalUInt16Val(pItemFrameData+4, 2);

	// 计算备注信息大小
	UINT commentSize = CalUInt16Val(pItemFrameData+6, 2);

	// 偏移量
	UINT offset = 10;

	LOGICTRL(UART_DEBUG, "titleSize = %d, artistSize = %d, commentSize = %d\n", titleSize, artistSize, commentSize);

	// 临时存放信息(因为是Unicode编码，存放区长度为偶数 +2存放结束标识)
	char temp[ID3_ITEM_LEN + 2] = { 0 };

	memcpy(temp, pItemFrameData+offset, Min(titleSize, ID3_ITEM_LEN));
	CharsetConvert("UTF-16LE", "UTF-8", temp, Min(titleSize, ID3_ITEM_LEN), pID3Info->title, ID3_ITEM_LEN);
	offset += titleSize;

	// 取得艺术家信息
	memset(temp, 0, ID3_ITEM_LEN);
	memcpy(temp, pItemFrameData+offset, Min(artistSize, ID3_ITEM_LEN));
	CharsetConvert("UTF-16LE", "UTF-8", temp, Min(artistSize, ID3_ITEM_LEN), pID3Info->artist, ID3_ITEM_LEN);
	offset += artistSize;

	// 取得版权信息
	offset += copyRightSize;

	// 取得备注信息
	memset(temp, 0, ID3_ITEM_LEN);
	memcpy(temp, pItemFrameData+offset, Min(commentSize, ID3_ITEM_LEN));
	CharsetConvert("UTF-16LE", "UTF-8", temp, Min(commentSize, ID3_ITEM_LEN), pID3Info->comment, ID3_ITEM_LEN);
	offset += commentSize;

	return true;
}

bool CWMAID3Parser::ParseExtendFrame(const BYTE *pItemFrameData, UINT frameSize,
		S_ID3_INFO *pID3Info, S_PIC_INFO *pPicInfo) {
	// 计算扩展信息数量
	UINT exInfoCounts = CalUInt16Val(pItemFrameData, 2);

	LOGICTRL(UART_DEBUG, "ParseExtendFrame exInfoCounts = %d\n", exInfoCounts);

	// 地址偏移量
	UINT offset = 2;

	UINT exNameSize = 0;
	UINT exFlagVal = 0;
	UINT valSize = 0;

	bool result = false;

	// 取扩展信息
	for (unsigned exIndex = 0; exIndex < exInfoCounts; ++exIndex) {
		// 计算扩展名大小
		exNameSize = CalUInt16Val(pItemFrameData+offset, 2);
		offset += 2;

		// 取得扩展名称
		wchar_t exName[50] = { 0 };
		memcpy(exName, pItemFrameData+offset, exNameSize);
		offset += exNameSize;

		// 取得扩展标识FLAG值
		exFlagVal = CalUInt16Val(pItemFrameData+offset, 2);
		offset += 2;

		// 取得实际值的大小
		valSize = CalUInt16Val(pItemFrameData+offset, 2);
		offset += 2;

		LOGICTRL(UART_DEBUG, "exNameSize= %d, exFlagVal = %d, valSize = %d\n", exNameSize, exFlagVal, valSize);

		if (pPicInfo != NULL) {		// 图片与其他分开解析(不空情况下，只解析图片数据)
			if (WStringIsSame(exName, WM_PICTURE)) {
				LOGICTRL(UART_DEBUG, "is WM/Picture. valSize = %d\n", valSize);
				result = ParsePicFrame(pItemFrameData+offset, valSize, pPicInfo);
				break;
			}
		} 
		
		if (pID3Info != NULL) {
			if (exFlagVal != 3) {	// 字符串类型
				if (WStringIsSame(exName, WM_ALBUMTITLE)) {		// 专辑信息
					LOGICTRL(UART_DEBUG, "is WM/AlbumTitle\n");

					char temp[ID3_ITEM_LEN + 2] = { 0 };
					memcpy(temp, pItemFrameData+offset, Min(valSize, ID3_ITEM_LEN));
					CharsetConvert("UTF-16LE", "UTF-8", temp, Min(valSize, ID3_ITEM_LEN), pID3Info->album, ID3_ITEM_LEN);

					result = true;
				} else if (WStringIsSame(exName, WM_YEAR)) {	// 年份信息
					LOGICTRL(UART_DEBUG, "is WM/Year\n");

					char temp[ID3_ITEM_LEN + 2] = { 0 };
					memcpy(temp, pItemFrameData+offset, Min(valSize, ID3_ITEM_LEN));
					CharsetConvert("UTF-16LE", "UTF-8", temp, Min(valSize, ID3_ITEM_LEN), pID3Info->year, ID3_ITEM_LEN);

					result = true;
				}
			}
		}

		offset += valSize;
	}

	return result;
}

bool CWMAID3Parser::ParsePicFrame(const BYTE *pPicFrameData, UINT frameSize, S_PIC_INFO *pPicInfo) {
	// 跳过第一个字节
	int offset = 1;

	UINT picLen = CalUInt32Val(pPicFrameData+offset, 4);
	offset += 4;

	LOGICTRL(UART_DEBUG, "ParsePicFrame picLen = %d\n", picLen);

	if (picLen >= frameSize-offset) {
		return false;
	}

	// MIME type: image/jpeg, image/png
	while (!((pPicFrameData[offset] == 0) && (pPicFrameData[offset+1] == 0))) {
		offset += 2;
	}
	offset += 2;

	// Description
	while (!((pPicFrameData[offset] == 0) && (pPicFrameData[offset+1] == 0))) {
		offset += 2;
	}
	offset += 2;

	pPicInfo->dataLen = picLen;
	pPicInfo->pData = new BYTE[pPicInfo->dataLen];
	memcpy(pPicInfo->pData, pPicFrameData+offset, pPicInfo->dataLen);

	return true;
}
