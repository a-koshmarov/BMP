//
// Created by Alexander on 07.01.2018.
//

#ifndef SER_BMP_H
#define SER_BMP_H

#include <stdio.h>

typedef unsigned long int DWORD;
typedef long int LONG;
typedef unsigned short int WORD;
typedef unsigned char BYTE;

typedef struct plt_pixel {
    BYTE b, g, r, a;
} p_pxl;

typedef struct tagBitMapFileHeader {
    DWORD   bfSize, bfOffBits;
    WORD    bfType, bfReserved1, bfReserved2;
} bitMapFileHeader;

typedef struct tagBitMapInfoHeader {
    DWORD  biSize, biCompression, biSizeImage, biClrUsed, biClrImportant;
    LONG   biWidth, biHeight, biXPelsPerMeter, biYPelsPerMeter;
    WORD   biPlanes, biBitCount;
} bitMapInfoHeader;

typedef struct pixel {
    BYTE b, g, r;
} pxl;



#endif //SER_BMP_H
