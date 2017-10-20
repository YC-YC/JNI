/*
 * ID3.cpp
 *
 *  Created on: 2016-1-6
 *      Author: guoxs
 */

#include <iostream>

#include "ID3Manager.h"
#include "MP3ID3Parser.h"
#include "WMAID3Parser.h"
#include "M4AID3Parser.h"

#include "CustomFun.h"
#include "Debug.h"


CID3Manager::CID3Manager() {
	memset(&m_id3Info, 0, sizeof(m_id3Info));
	
	m_pMP3ID3Parser = new CMP3ID3Parser;
	m_pWMAID3Parser = new CWMAID3Parser;
	m_pM4AID3Parser = new CM4AID3Parser;
		
	m_pMP3ID3Parser->SetNextParser(m_pWMAID3Parser);
//	m_pWMAID3Parser->SetNextParser(m_pM4AID3Parser);
}

CID3Manager::~CID3Manager() {
	delete m_pMP3ID3Parser;
	delete m_pWMAID3Parser;
	delete m_pM4AID3Parser;
}

bool CID3Manager::ParseID3(const char *pPath) {
	memset(&m_id3Info, 0, sizeof(m_id3Info));

	return m_pMP3ID3Parser->ParseID3(pPath, &m_id3Info);
}

bool CID3Manager::ParseID3Pic(const char *pPath, const char *pSavePicPath) {
	S_PIC_INFO picInfo = { 0 };
	bool result = false;

	if (m_pMP3ID3Parser->ParseID3Pic(pPath, &picInfo)) {
		result = SaveDataToFile((const char *)picInfo.pData, picInfo.dataLen, pSavePicPath);

		// 记得释放内存
		delete[] picInfo.pData;
	}

	return result;
}

jbyteArray CID3Manager::ParseID3Pic(const char *pPath, JNIEnv *env) {
	if (env == NULL) {
		return NULL;
	}

	S_PIC_INFO picInfo = { 0 };

	if (m_pMP3ID3Parser->ParseID3Pic(pPath, &picInfo)) {
		jbyteArray dataArray = env->NewByteArray(picInfo.dataLen);
		env->SetByteArrayRegion(dataArray, 0, picInfo.dataLen, (jbyte*)picInfo.pData);

		// 记得释放内存
		delete[] picInfo.pData;

		return dataArray;
	}

	return NULL;
}
