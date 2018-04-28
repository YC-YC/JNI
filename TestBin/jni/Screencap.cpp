/*
 * TestSpyFile.cpp
 *
 *  Created on: 2018-4-9
 *      Author: YC2
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
//#include <sys/soundcard.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "comdef.h"
#ifdef __cplusplus
extern "C"
{
#endif

static unsigned char sg_BHeader[] = {
    0x42, 0x4D, 0x36, 0x58, 0x02, 0x00, 0x00, 0x00,  0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
    0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0xF0, 0x00,  0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define RGB565TO1555(rgb) ((unsigned short)((unsigned short)(rgb & 0x001f) | ((unsigned short)(rgb & 0xffc0) >> 1)))

void SaveBMPFile(unsigned char *raw, const char *filename)
{
    unsigned short *p = (unsigned short *)raw;
    typedef unsigned int UINT;
    typedef unsigned char UCHAR;
    UINT m_Width = 1920, m_Height = 720;
    UINT i, j;
    int bmp = open(filename, O_WRONLY | O_CREAT);
    if(bmp < 0)
        return;
    sg_BHeader[0x02] = (UCHAR)(m_Width * m_Height * 2 + 0x36) & 0xff;
    sg_BHeader[0x03] = (UCHAR)((m_Width * m_Height * 2 + 0x36) >> 8) & 0xff;
    sg_BHeader[0x04] = (UCHAR)((m_Width * m_Height * 2 + 0x36) >> 16) & 0xff;
    sg_BHeader[0x05] = (UCHAR)((m_Width * m_Height * 2 + 0x36) >> 24) & 0xff;
    sg_BHeader[0x12] = (UCHAR)m_Width & 0xff;
    sg_BHeader[0x13] = (UCHAR)(m_Width >> 8) & 0xff;
    sg_BHeader[0x14] = (UCHAR)(m_Width >> 16) & 0xff;
    sg_BHeader[0x15] = (UCHAR)(m_Width >> 24) & 0xff;
    sg_BHeader[0x16] = (UCHAR)m_Height & 0xff;
    sg_BHeader[0x17] = (UCHAR)(m_Height >> 8) & 0xff;
    sg_BHeader[0x18] = (UCHAR)(m_Height >> 16) & 0xff;
    sg_BHeader[0x19] = (UCHAR)(m_Height >> 24) & 0xff;
    write(bmp, sg_BHeader, sizeof(sg_BHeader));
    for(i = 0; i < m_Height; i++)
    {
        unsigned short *c = p + (m_Height - 1 - i) * m_Width;
        unsigned short cc;
        for(j = 0; j < m_Width; j++)
        {
            cc = RGB565TO1555(*(c + j));
//            cc = *(c + j);
            write(bmp, &cc, 2);
        }
    }
    close(bmp);
}

int testScreencap()
{
    unsigned char buf[1920*720*2];
    char *filename;
    int fb;


    fb = open("/dev/graphics/fb0", O_RDONLY);
    if(fb < 0)
        exit(1);
//    if(argc == 2)
//        filename = argv[1];
//    else
//        exit(1);
    LOGI("reading screen...\n");
    read(fb, buf, 1920*720*2);
    close(fb);
    LOGI("saving screen...\n");
    SaveBMPFile(buf, "/mnt/sdcard/test.png");
    LOGI("file %s created successfully\n", filename);
    exit(0);
}

#ifdef __cplusplus
}
#endif
