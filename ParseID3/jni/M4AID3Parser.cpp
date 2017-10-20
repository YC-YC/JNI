/*
 * M4AID3Parser.cpp
 *
 *  Created on: 2016-1-16
 *      Author: guoxs
 */

#include <iostream>

#include "M4AID3Parser.h"
#include "CustomFun.h"
#include "Debug.h"


bool CM4AID3Parser::HandleParseID3(FILE *pM4AFile, S_ID3_INFO *pID3Info) {
	if (fseek(pM4AFile, 0, SEEK_SET)) {
		return false;
	}
	
	LOGICTRL(UART_DEBUG, "CM4AID3Parser::HandleParseID3++++++++++");

	BYTE sizeArray[4] = { 0 };
	if (!fread(sizeArray, 4, 1, pM4AFile)) {
		return false;
	}

	BYTE flagArray[4] = { 0 };
	if (!fread(flagArray, 4, 1, pM4AFile) || strncmp((const char *)flagArray, "ftyp", 4)) {
		return false;
	}

	// 把文件指针移动到ATOM开始的位置
	if (fseek(pM4AFile, GetSize(sizeArray)-8, SEEK_CUR)) {
		return false;
	}

	// 每个ATOM的格式都是4个字节的大小加上4个字节的标识符
	// 循环读取找出需要解析的标识符进行解析
	M4ATAGATOM_ID curAtom = M4ATAGATOM_ERROR;
	bool result = false;

	while (fread(sizeArray, 4, 1, pM4AFile) && fread(flagArray, 4, 1, pM4AFile)) {
		curAtom = M4ATAGATOM_ERROR;

		// 这些ATOM之后紧跟着是所属子层次的ATOM，不需要移动文件指针
		if (!strncmp((const char *)flagArray, "moov", 4) ||			// moov
			!strncmp((const char *)flagArray, "trak", 4) || 		// trak
			!strncmp((const char *)flagArray, "mdia", 4) || 		// mdia
			!strncmp((const char *)flagArray, "minf", 4) || 		// minf
			!strncmp((const char *)flagArray, "stbl", 4) || 		// stbl
			!strncmp((const char *)flagArray, "udta", 4) || 		// udta
			!strncmp((const char *)flagArray, "ilst", 4)) { 		// ilst      TAG信息都在这个ATOM之下
			continue;
		} else if (!strncmp((const char *)flagArray, "meta", 4)) {	// 此ATOM之后的4个字节是大小需要向后移动4个字节的文件指针
			fseek(pM4AFile, 4, SEEK_CUR);
			continue;
		} else if (flagArray[0] == 0xA9) {							// 解析专辑、艺术家、名称、年份日期，这些第一个字节值为0xA9
			if (!strncmp((const char *)(flagArray+1), "alb", 3)) {
				curAtom = M4ATAGATOM_ALBUM;						// 专辑
			} else if (!strncmp((const char *)(flagArray+1), "ART", 3)) {
				curAtom = M4ATAGATOM_ARTIST;					// 艺术家
			} else if (!strncmp((const char *)(flagArray+1), "nam", 3)) {
				curAtom = M4ATAGATOM_TITLE;						// 标题
			} else if (!strncmp((const char *)(flagArray+1), "day", 3)) {
				curAtom = M4ATAGATOM_DATE; 						// 日期
			}
		}

		if (curAtom != M4ATAGATOM_ERROR) {
			/*
			 * 给出需要解析的ATOM的格式及实际数据例子如下:
			 * |    XXXX     |     AAAA     |    xxxx     |     data    |    ver    |   flag   |  reserved   | realdata    |
			 *    总长度4字节         	 标识符4字节           		  长度4字节         		 固定符号4字节            1字节                  3字节               		保留4字节           剩余实际数据
			 * | 00 00 00 1C | A9 61 6C 62  | 00 00 00 14 | 64 61 74 61 |     00    | 00 00 01 | 00 00 00 00 | 43 43 43 43 |
			 *     总长28                  标识符A9 alb      长度20                  字符data                                         实际数据CCCC
			 * 其中流派的实际数据为2个字节，给出的是索引值，需要拿这个索引值在流派类型数组中取出流派字符串
			 * 专辑、艺术家、名称、日期的实际数据是UTF-8编码
			 * 封面的实际数据就是整个图片数据
			 * 当前文件指针位置为长度xxxx的起始位置
			 * 读取长度及标识符，读取失败直接跳出循环结束
			 */

			BYTE atomSizeArray[4] = { 0 };
			if (fread(atomSizeArray, 4, 1, pM4AFile) && fread(flagArray, 4, 1, pM4AFile)) {
				UINT dataLen = GetSize(atomSizeArray) - 16;	// 计算实际数据长度

				// 判断长度及标识符是否正确
				if ((GetSize(atomSizeArray)+8 == GetSize(sizeArray)) &&
					!strncmp((const char *)flagArray, "data", 4) && (dataLen > 0)) {
					// 当前文件指针位于ver开始处，向后移动8个字节到实际数据处
					fseek(pM4AFile, 8, SEEK_CUR);

					BYTE *pData = new BYTE[dataLen];
					memset(pData, 0, dataLen);

					// 读取实际数据
					bool readResult = false;
					if (fread(pData, dataLen, 1, pM4AFile)) {
						readResult = true;

						switch (curAtom) {
						case M4ATAGATOM_ALBUM: 	// 专辑
							memcpy(pID3Info->album, pData, Min(dataLen, ID3_ITEM_LEN));
							result = true;
							break;
							memcpy(pID3Info->artist, pData, Min(dataLen, ID3_ITEM_LEN));
						case M4ATAGATOM_ARTIST: // 艺术家
							result = true;
							break;
						case M4ATAGATOM_TITLE: 	// 标题
							memcpy(pID3Info->title, pData, Min(dataLen, ID3_ITEM_LEN));
							result = true;
							break;
						case M4ATAGATOM_DATE:  	// 日期
							memcpy(pID3Info->year, pData, Min(dataLen, ID3_ITEM_LEN));
							result = true;
							break;
						default:
							break;
						}
					}

					delete[] pData;

					if (!readResult) {	// 读取文件错误直接结束
						break;
					}
				} else {	// 格式不对，移动文件指针到下一个ATOM开始的位置，基本不会发生这种情况
					fseek(pM4AFile, GetSize(sizeArray)-16, SEEK_CUR);
				}
			} else {	// 发生了读取文件失败则直接结束
				break;
			}
		} else {		// 非解析ATOM，移动文件指针到下一个ATOM的开始位置
			fseek(pM4AFile, GetSize(sizeArray)-8, SEEK_CUR);
		}
	}

	LOGICTRL(UART_DEBUG, "CM4AID3Parser::HandleParseID3----------");

	return result;
}

bool CM4AID3Parser::HandleParseID3Pic(FILE *pM4AFile, S_PIC_INFO *pPicInfo) {
	if (fseek(pM4AFile, 0, SEEK_SET)) {
		return false;
	}

	LOGICTRL(UART_DEBUG, "CM4AID3Parser::HandleParseID3Pic++++++++++");

	BYTE sizeArray[4] = { 0 };
	if (!fread(sizeArray, 4, 1, pM4AFile)) {
		return false;
	}

	BYTE flagArray[4] = { 0 };
	if (!fread(flagArray, 4, 1, pM4AFile) || strncmp((const char *)flagArray, "ftyp", 4)) {
		return false;
	}

	// 把文件指针移动到ATOM开始的位置
	if (fseek(pM4AFile, GetSize(sizeArray)-8, SEEK_CUR)) {
		return false;
	}

	bool result = false;

	while (fread(sizeArray, 4, 1, pM4AFile) && fread(flagArray, 4, 1, pM4AFile)) {
		// 这些ATOM之后紧跟着是所属子层次的ATOM，不需要移动文件指针
		if (!strncmp((const char *)flagArray, "moov", 4) ||			// moov
			!strncmp((const char *)flagArray, "trak", 4) || 		// trak
			!strncmp((const char *)flagArray, "mdia", 4) || 		// mdia
			!strncmp((const char *)flagArray, "minf", 4) || 		// minf
			!strncmp((const char *)flagArray, "stbl", 4) || 		// stbl
			!strncmp((const char *)flagArray, "udta", 4) || 		// udta
			!strncmp((const char *)flagArray, "ilst", 4)) { 		// ilst      TAG信息都在这个ATOM之下
			continue;
		} else if (!strncmp((const char *)flagArray, "meta", 4)) {	// 此ATOM之后的4个字节是大小需要向后移动4个字节的文件指针
			fseek(pM4AFile, 4, SEEK_CUR);
			continue;
		} else if (!strncmp((const char *)flagArray, "covr", 4)) {	// 解析封面图片
			BYTE atomSizeArray[4] = { 0 };
			if (fread(atomSizeArray, 4, 1, pM4AFile) && fread(flagArray, 4, 1, pM4AFile)) {
				UINT dataLen = GetSize(atomSizeArray) - 16;	// 计算实际数据长度

				if ((GetSize(atomSizeArray)+8 == GetSize(sizeArray)) &&
					!strncmp((const char *)flagArray, "data", 4) && (dataLen > 0)) {
					// 当前文件指针位于ver开始处，向后移动8个字节到实际数据处
					fseek(pM4AFile, 8, SEEK_CUR);

					BYTE *pData = new BYTE[dataLen];
					memset(pData, 0, dataLen);

					if (fread(pData, dataLen, 1, pM4AFile)) {
						int offset = 0;
						// jpeg格式图片, 开始标志: 0xFF 0xD8, 结束标志: 0xFF 0xD9
						while ((offset < dataLen-5) && !((pData[offset] == 0xFF) && (pData[offset+1] == 0xD8))) {
							++offset;
						}

						if (offset < dataLen-5) {
							pPicInfo->dataLen = dataLen - offset;
							pPicInfo->pData = new BYTE[pPicInfo->dataLen];
							memcpy(pPicInfo->pData, pData+offset, pPicInfo->dataLen);

							result = true;
						}
					}

					delete[] pData;
				}
			}

			break;
		}

		fseek(pM4AFile, GetSize(sizeArray)-8, SEEK_CUR);
	}

	LOGICTRL(UART_DEBUG, "CM4AID3Parser::HandleParseID3Pic----------");

	return result;
}

UINT CM4AID3Parser::GetSize(const BYTE sizeArray[]) {
	return ((sizeArray[0]<<24) | (sizeArray[1]<<16) |
			(sizeArray[2]<<8) | sizeArray[3]);
}
