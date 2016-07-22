/*
 * BaseID3Parser.h
 *
 *  Created on: 2016-1-16
 *      Author: guoxs
 */

#ifndef _BASE_ID3_PARSER_H_
#define _BASE_ID3_PARSER_H_

#include "CommDef.h"

class CBaseID3Parser {
public:
	CBaseID3Parser(): m_pNextParser(NULL) { }

	bool ParseID3(const char *pPath, S_ID3_INFO *pID3Info);
	bool ParseID3Pic(const char *pPath, S_PIC_INFO *pPicInfo);
	
	void SetNextParser(CBaseID3Parser *pNextParser) { m_pNextParser = pNextParser; }
	
protected:	
	virtual bool HandleParseID3(FILE *pFile, S_ID3_INFO *pID3Info) = 0;	
	virtual bool HandleParseID3Pic(FILE *pFile, S_PIC_INFO *pPicInfo) = 0;
	
private:
	bool ParseID3(FILE *pFile, S_ID3_INFO *pID3Info);
	bool ParseID3Pic(FILE *pFile, S_PIC_INFO *pPicInfo);
	
protected:
	CBaseID3Parser *m_pNextParser;
};

#endif /* _BASE_ID3_PARSER_H_ */
