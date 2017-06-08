/*
 * MP3ID3Parser.cpp
 *
 *  Created on: 2016-1-11
 *      Author: guoxs
 */

#include <iostream>

#include "MP3ID3Parser.h"
#include "CustomFun.h"
#include "Debug.h"


bool CMP3ID3Parser::HandleParseID3(FILE *pMP3File, S_ID3_INFO *pID3Info) {
	if (fseek(pMP3File, 0, SEEK_SET)) {
		return false;
	}

	LOGICTRL(UART_DEBUG, "CMP3ID3Parser::HandleParseID3++++++++++");

	bool result = false;
	BYTE flagHeader[10] = { 0 };
	if (fread(flagHeader, 10, 1, pMP3File)) {		// 读标签头10字节
		if (IsID3V2_3(flagHeader)) {				// ID3V2_3
			// ID3实际内容长度
			UINT dataLen = flagHeader[6]*0x200000 + flagHeader[7]*0x4000
								+ flagHeader[8]*0x80 + flagHeader[9];

			LOGICTRL(UART_DEBUG, "CMP3ID3Parser::ParseID3 dataLen = %d", dataLen);
			if (dataLen < 2*1024*1024) {	// 大于1M，不继续解析
				BYTE *pID3Data = new BYTE[dataLen];
				if (fread(pID3Data, dataLen, 1, pMP3File)) {
					result = ParseID3V2_3(pID3Data, dataLen, pID3Info, NULL);
				}
				delete[] pID3Data;
			}
		} else {
			BYTE id3Data[128] = { 0 };
			fseek(pMP3File, -128, SEEK_END);
			if (fread(id3Data, 128, 1, pMP3File) && IsID3V1(id3Data)) {
				result = ParseID3V1(id3Data+3, pID3Info);
			}
		}
	}
	
	LOGICTRL(UART_DEBUG, "CMP3ID3Parser::HandleParseID3----------");

	return result;
}

bool CMP3ID3Parser::HandleParseID3Pic(FILE *pMP3File, S_PIC_INFO *pPicInfo) {
	if (fseek(pMP3File, 0, SEEK_SET)) {
		return false;
	}

	LOGICTRL(UART_DEBUG, "CMP3ID3Parser::HandleParseID3Pic++++++++++");

	bool result = false;
	BYTE flagHeader[10] = { 0 };
	if (fread(flagHeader, 10, 1, pMP3File)) {	// 读标签头10字节
		if (IsID3V2_3(flagHeader)) {			// ID3V2_3才可能有专辑封面图片
			// ID3实际内容长度
			UINT dataLen = flagHeader[6]*0x200000 + flagHeader[7]*0x4000
							+ flagHeader[8]*0x80 + flagHeader[9];

			if (dataLen < 1024*1024) {	// 大于1M，不继续解析
				BYTE *pID3Data = new BYTE[dataLen];
				if (fread(pID3Data, dataLen, 1, pMP3File)) {
					result = ParseID3V2_3(pID3Data, dataLen, NULL, pPicInfo);
				}
				delete[] pID3Data;
			}
		}
	}
	
	LOGICTRL(UART_DEBUG, "CMP3ID3Parser::HandleParseID3Pic----------");

	return result;
}

bool CMP3ID3Parser::IsID3V2_3(const BYTE *pFlagHeader) const {
	return (strncmp((const char *)pFlagHeader, "ID3", 3) == 0) &&
			((pFlagHeader[3] == 3) || (pFlagHeader[3] == 4)) &&
			(pFlagHeader[4] == 0);
}

bool CMP3ID3Parser::IsID3V1(const BYTE *pFlagHeader) const {
	return (strncmp((const char *)pFlagHeader, "TAG", 3) == 0);
}

bool CMP3ID3Parser::ParseID3V2_3(const BYTE *pID3Data, UINT dataLen, 
		S_ID3_INFO *pID3Info, S_PIC_INFO *pPicInfo) {
	LOGICTRL(UART_DEBUG, "CMP3ID3Parser::ParseID3V2_3++++++++++");

	bool result = false;
	
	while (dataLen > 10) {
		UINT frameLen = pID3Data[4]*0x1000000 + pID3Data[5]*0x10000 +
				pID3Data[6]*0x100 + pID3Data[7];

		if (frameLen > dataLen) {
			return false;
		}

		if (pPicInfo != NULL) {	
			if (strncmp((const char *)pID3Data, "APIC", 4) == 0) {				// 图片标签
				result = ParseAPICData(pID3Data+10, frameLen, pPicInfo);		// 解析图片
				break;
			}
		} 
		
		if (pID3Info != NULL) {
			if (strncmp((const char *)pID3Data, "TIT2", 4) == 0) {				// 曲目标签
				if (ParseDataBlock(pID3Data+10, frameLen, pID3Info->title)) {
					result = true;
				}
			} else if (strncmp((const char *)pID3Data, "TPE1", 4) == 0) {		// 作者标签
				if (ParseDataBlock(pID3Data+10, frameLen, pID3Info->artist)) {
					result = true;
				}
			} else if (strncmp((const char *)pID3Data, "TALB", 4) == 0) {		// 专辑标签
				if (ParseDataBlock(pID3Data+10, frameLen, pID3Info->album)) {
					result = true;
				}
			}
		}

		dataLen = dataLen - frameLen - 10;
		pID3Data = pID3Data + frameLen + 10;
	}
	
	return result;
}

bool CMP3ID3Parser::ParseID3V1(const BYTE *pID3Data, S_ID3_INFO *pID3Info) {
	char temp[ID3_ITEM_LEN + 1] = { 0 };

	memcpy(temp, pID3Data, 30);
	CharsetConvert("GBK", "UTF-8", temp, 30, pID3Info->title, ID3_ITEM_LEN);

	memcpy(temp, pID3Data+30, 30);
	CharsetConvert("GBK", "UTF-8", temp, 30, pID3Info->artist, ID3_ITEM_LEN);

	memcpy(temp, pID3Data+60, 30);
	CharsetConvert("GBK", "UTF-8", temp, 30, pID3Info->album, ID3_ITEM_LEN);
	
	return true;
}

bool CMP3ID3Parser::ParseAPICData(const BYTE *pAPICFrameData, UINT apicFrameLen, S_PIC_INFO *pPicInfo) {
	LOGICTRL(UART_DEBUG, "CMP3ID3Parser::ParseAPICData++++++++++");

	BYTE encoding = *pAPICFrameData;	// 编码格式
	int offset = 1;

	offset += (strlen((const char *)(pAPICFrameData+offset)) + 1);

#if 0	// 不根据编码格式来判断，直接查找0xFF 0xD8开始位置
	if ((encoding == 0x00) || (encoding == 0x03)) {		// ISO 8859-1 or UTF-8
		offset += (strlen((const char *)(pAPICFrameData+offset)) + 1);
	} else {
		while (!((pAPICFrameData[offset] == 0) && (pAPICFrameData[offset+1] == 0))) {
			offset += 2;
		}
		offset += 2;
	}

	// 图片数据以0xFF、0xD8开始
	if ((pAPICFrameData[offset] != 0xFF) || (pAPICFrameData[offset+1] != 0xD8)) {
		return false;
	}
#endif

	// jpeg格式图片, 开始标志: 0xFF 0xD8, 结束标志: 0xFF 0xD9
	while ((offset < apicFrameLen-5) && !((pAPICFrameData[offset] == 0xFF) && (pAPICFrameData[offset+1] == 0xD8))) {
		++offset;
	}

	if (offset == apicFrameLen-5) {
		return false;
	}
	
	pPicInfo->dataLen = apicFrameLen - offset;
	pPicInfo->pData = new BYTE[pPicInfo->dataLen];
	memcpy(pPicInfo->pData, pAPICFrameData+offset, pPicInfo->dataLen);

	LOGICTRL(UART_DEBUG, "CMP3ID3Parser::ParseAPICData pPicInfo->dataLen = %d++++++++++", pPicInfo->dataLen);

	return true;
}

bool CMP3ID3Parser::ParseDataBlock(const BYTE *pSrc, int len, char *pDest) {
	if (len > ID3_ITEM_LEN) {
		len = ID3_ITEM_LEN;
	}
	
	bool result = false;

	/*
	 * 0：ISO-8859-1编码
	 * 1：UTF-16LE编码(Unicode)
	 * 2：UTF-16BE编码（大端）
	 * 3：UTF-8编码
	 *
	 */
	int charset = *pSrc++;
	--len;
	LOGICTRL(UART_DEBUG, "CMP3ID3Parser::ParseDataBlock len = %d, charset = %d++++++++++", len, charset);

	switch (charset) {
	case 1:			// UTF-16LE
	{
		if ((len > 4) && (strncmp((const char *)pSrc, "eng", 4) == 0)) {
			pSrc += 4;
			len -= 4;
		}
		bool bBigEndian = false;
		if ((len > 2) && (pSrc[0] == 0xFF) && (pSrc[1] == 0xFE)) {
			pSrc += 2;
			len -= 2;
		}
		else if ((len > 2) && (pSrc[0] == 0xFE) && (pSrc[1] == 0xFF)) {
			pSrc += 2;
			len -= 2;
			bBigEndian = true;
		}

		if (len%2 != 0) {
			--len;	// 确保是偶数位
		}

		if (len > 0) {
			char temp[ID3_ITEM_LEN + 1] = { 0 };
			memcpy(temp, pSrc, len);
			if (bBigEndian){
				result = CharsetConvert("UTF−16BE", "UTF-8", temp, len, pDest, ID3_ITEM_LEN);
			}
			else{
				result = CharsetConvert("UTF-16LE", "UTF-8", temp, len, pDest, ID3_ITEM_LEN);
			}

			if (!result) {	// 大端数据
				LOGICTRL(UART_DEBUG, "CMP3ID3Parser::ParseDataBlock CharsetConvert Big Eng!");
				BYTE *pTemp = (BYTE *)temp;
				for (int i = 0; i < len; i += 2) {
					BYTE t = pTemp[i];
					pTemp[i] = pTemp[i+1];
					pTemp[i+1] = t;
				}

				// 保险起见，清除一下pDest内存
				memset(pDest, 0, ID3_ITEM_LEN);
				result = CharsetConvert("UTF-16LE", "UTF-8", temp, len, pDest, ID3_ITEM_LEN);
			}
		}
	}
		break;
	case 2:			// UTF-16BE
		break;
	case 0:			// ISO-8859-1
	case 3:			// UTF-8
		while ((len > 0) && (*pSrc == 0)) {		// 有些ID3信息前面有若干个0，需清除
			++pSrc;
			--len;
		}

		if ((len > 4) && (strncmp((const char *)pSrc, "chi", 4) == 0)) {	// 有些备注是以chi\0作为开始标记
			pSrc += 4;
			len -= 4;
		}

		if (len > 0) {
			if (charset == 0) {
				char temp[ID3_ITEM_LEN + 1] = { 0 };
				memcpy(temp, pSrc, len);
				CharsetConvert("GBK", "UTF-8", temp, len, pDest, ID3_ITEM_LEN);
			} else if (charset == 3) {
				memcpy(pDest, pSrc, len);
			}
			
			result = true;
		}
		break;
	default:
		break;
	}
	
	return result;
}
