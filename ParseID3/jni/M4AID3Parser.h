/*
 * M4AID3Parser.h
 *
 *  Created on: 2016-1-16
 *      Author: guoxs
 */

#ifndef _M4A_ID3_PARSER_H_
#define _M4A_ID3_PARSER_H_

#include "CommDef.h"
#include "BaseID3Parser.h"

/*************************************************************************
1、MP4(或M4A)文件开头数据字节结构
+--------------------------------+
|      Header Size (4 bytes)     |大小是按字节顺序存储
+--------------------------------+
|      固定标记 (4 bytes)ftyp     |
+--------------------------------+
| 类型 (8 bytes) M4A、mp42、isom等 |
+--------------------------------+
|  剩余字节为ASCII编码的字符串信息  |
+--------------------------------+
2、此后每一个ATOM的结构都是：4个字节的长度+4个字节的标识符
3、ATOM之间具有包含关系，当A包含B时且B是A的第一个子ATOM，格式如下：
	XXXX AAAA xxxx BBBB xxxx CCCC ....
	其中XXXX 4个字节表示出标记为AAAA的ATOM的总的大小
	后续子ATOM包含在这个总的大小之内
	也就是XXXX = 8 + xxxx(B) + xxxx(C) + ...
	上式中的8表示4个长度字节XXXX以及4个标识符字节AAAA
*************************************************************************/

// 定义用到的ATOM的ID
enum M4ATAGATOM_ID {
	M4ATAGATOM_ERROR = 0,   // 初始化值
	M4ATAGATOM_TITLE,       // 标题
	M4ATAGATOM_ARTIST,      // 艺术家
	M4ATAGATOM_ALBUM,       // 专辑
	M4ATAGATOM_DATE,        // 日期
};

class CM4AID3Parser: public CBaseID3Parser {
protected:
	virtual bool HandleParseID3(FILE *pM4AFile, S_ID3_INFO *pID3Info);
	virtual bool HandleParseID3Pic(FILE *pM4AFile, S_PIC_INFO *pPicInfo);

private:
	UINT GetSize(const BYTE sizeArray[]);
};

#endif /* _M4A_ID3_PARSER_H_ */
