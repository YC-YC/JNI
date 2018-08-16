/*
 * TestStd.cpp
 *C++ std库测试
 *  Created on: 2018-5-8
 *      Author: YC2
 */

#include "comdef.h"
#include "MD5.h"
#include <iostream>


using namespace std;
#ifdef __cplusplus
extern "C"
{
#endif
/**
 *
 */

/*string FileDigest(const string &file) {

    ifstream in(file.c_str(), ios::binary);
    if (!in)
        return "";

    MD5 md5;
    std::streamsize length;
    char buffer[1024];
    while (!in.eof()) {
        in.read(buffer, 1024);
        length = in.gcount();
        if (length > 0)
            md5.update(buffer, length);
    }
    in.close();
    return md5.toString();
}*/

void testMD5(){
	LOGI("testMD5");
	string md5 = MD5("/storage/udisk/test_mcu_upgrade/update.bin-16").toString();
	const byte* pMd5 = MD5("/storage/udisk/test_mcu_upgrade/update.bin-16").digest();
	LOGI("file digest = %s, equal = %d", md5.c_str(), strcasecmp("25ECC30812940C863846E5EC67D101C8", md5.c_str()));
	md5 = MD5("/storage/udisk/test_mcu_upgrade/update.bin-18").toString();
	LOGI("file 222 digest = %s, equal = %d", md5.c_str(), strcasecmp("25ECC30812940C863846E5EC67D101C8", md5.c_str()));

}

#ifdef __cplusplus
}
#endif
