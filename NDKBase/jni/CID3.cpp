/*
 * CID3.cpp
 *
 *  Created on: 2016-1-7
 *      Author: YC
 */

#include "CID3.h"
#include "debug.h"

CID3::CID3()
{
	TestAp_Printf(UART_DEBUG, "CID3::CID3()\r\n");
}
CID3::~CID3()
{


}
bool CID3::SetFilePath(const char* pPath)
{
	TestAp_Printf(UART_DEBUG, "CID3::SetFilePath = [%s]\r\n", pPath);
	return true;
}
const char* CID3::GetTitle()
{
	return "未知标题";
}
const char* CID3::GetArtist()
{
	return "未知作家";
}
const char* CID3::GetAlbum()
{
	return "未知专辑";
}
const char* CID3::GetComment()
{
	return "未知内容";
}
const char* CID3::GetYear()
{
	return "未知年份";
}

