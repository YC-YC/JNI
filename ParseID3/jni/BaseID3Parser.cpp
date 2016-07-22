/*
 * BaseID3Parser.cpp
 *
 *  Created on: 2016-1-16
 *      Author: guoxs
 */

#include <iostream>

#include "BaseID3Parser.h"
#include "Debug.h"


bool CBaseID3Parser::ParseID3(const char *pPath, S_ID3_INFO *pID3Info) {
	if ((pPath == NULL) || (pID3Info == NULL)) {
		return false;
	}

	FILE *pFile = fopen(pPath, "rb");
	if (pFile == NULL) {
		LOGICTRL(UART_DEBUG, "Open %s Fail!", pPath);
		return false;
	}
	
	bool result = ParseID3(pFile, pID3Info);	
	fclose(pFile);

	return result;
}

bool CBaseID3Parser::ParseID3Pic(const char *pPath, S_PIC_INFO *pPicInfo) {
	if ((pPath == NULL) || (pPicInfo == NULL)) {
		return false;
	}

	FILE *pFile = fopen(pPath, "rb");
	if (pFile == NULL) {
		LOGICTRL(UART_DEBUG, "Open %s Fail!", pPath);
		return false;
	}

	bool result = ParseID3Pic(pFile, pPicInfo);
	fclose(pFile);

	return result;
}

bool CBaseID3Parser::ParseID3(FILE *pFile, S_ID3_INFO *pID3Info) {
	bool result = HandleParseID3(pFile, pID3Info);
	if (!result && (m_pNextParser != NULL)) {
		result = m_pNextParser->ParseID3(pFile, pID3Info);
	}
	
	return result;
}

bool CBaseID3Parser::ParseID3Pic(FILE *pFile, S_PIC_INFO *pPicInfo) {
	bool result = HandleParseID3Pic(pFile, pPicInfo);
	if (!result && (m_pNextParser != NULL)) {
		result = m_pNextParser->ParseID3Pic(pFile, pPicInfo);
	}

	return result;
}
