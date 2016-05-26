/*
 * CID3.h
 *
 *  Created on: 2016-1-7
 *      Author: YC
 */

#ifndef CID3_H_
#define CID3_H_

#include <stdlib.h>
#include <stdio.h>

class CID3{

public:
	CID3();
	~CID3();
	bool SetFilePath(const char* pPath);
	const char* GetTitle();
	const char* GetArtist();
	const char* GetAlbum();
	const char* GetComment();
	const char* GetYear();

private:

};


#endif /* CID3_H_ */
