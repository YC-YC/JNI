/*
 * MP3ID3Parser.h
 *
 *  Created on: 2016-1-11
 *      Author: guoxs
 */

#ifndef _MP3_ID3_PARSER_H_
#define _MP3_ID3_PARSER_H_

#include "CommDef.h"
#include "BaseID3Parser.h"

class CMP3ID3Parser: public CBaseID3Parser {
protected:
	virtual bool HandleParseID3(FILE *pMP3File, S_ID3_INFO *pID3Info);
	virtual bool HandleParseID3Pic(FILE *pMP3File, S_PIC_INFO *pPicInfo);

private:
	bool IsID3V2_3(const BYTE *pFlagHeader) const;
	bool IsID3V1(const BYTE *pFlagHeader) const;
	
	bool ParseID3V2_3(const BYTE *pID3Data, UINT dataLen, S_ID3_INFO *pID3Info, S_PIC_INFO *pPicInfo);
	bool ParseID3V1(const BYTE *pID3Data, S_ID3_INFO *pID3Info);
	
	bool ParseAPICData(const BYTE *pAPICFrameData, UINT apicFrameLen, S_PIC_INFO *pPicInfo);	
	bool ParseDataBlock(const BYTE *pSrc, int len, char *pDest);
};

#endif /* _MP3_ID3_PARSER_H_ */
