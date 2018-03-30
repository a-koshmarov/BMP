#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bmp.h"

#define PATH_LEN 200

//Считывает FileHeader
void readFileHeader(FILE *f, bitMapFileHeader *bmpFh) {
    fread(&bmpFh->bfType, 2, 1, f);
    fread(&bmpFh->bfSize, 4, 1, f);
    fread(&bmpFh->bfReserved1, 2, 1, f);
    fread(&bmpFh->bfReserved2, 2, 1, f);
    fread(&bmpFh->bfOffBits, 4, 1, f);
}

//Считывает InfoHeader 
void readInfoHeader(FILE *f, bitMapInfoHeader *bmpIh) {
    fread(&bmpIh->biSize, 4, 1, f);
    fread(&bmpIh->biWidth, 4, 1, f);
    fread(&bmpIh->biHeight, 4, 1, f);
    fread(&bmpIh->biPlanes, 2, 1, f);
    fread(&bmpIh->biBitCount, 2, 1, f);
    fread(&bmpIh->biCompression, 4, 1, f);
    fread(&bmpIh->biSizeImage, 4, 1, f);
    fread(&bmpIh->biXPelsPerMeter, 4, 1, f);
    fread(&bmpIh->biYPelsPerMeter, 2, 1, f);
    fread(&bmpIh->biClrUsed, 4, 1, f);
    fread(&bmpIh->biClrImportant, 4, 1, f);
}

//Считывает пиксельные данные с палитрой
void readPaletteArray(FILE **f, bitMapInfoHeader *bmpIh, pxl *plt, pxl ***pxA) {
//    Отступ для 8-битного bmp
    int padding = (3 * bmpIh->biWidth) % 4;
    BYTE bytePxl;

//    Отступ для 4, 2, 1-битных bmp
    if (bmpIh->biBitCount == 4) {
        padding = (3 * ((bmpIh->biWidth & 1) == 0 ? bmpIh->biWidth : bmpIh->biWidth + 1) / 2) % 4;
    } else if (bmpIh->biBitCount == 2) {
//        newWidth = bmpIh->biWidth;
<<<<<<< HEAD
        padding = (3 * (bmpIh->biWidth + (8 - bmpIh->biWidth % 8)) / 4) % 4;
=======
//        Округляет кол-во пикселей вверх до числа, кратного кол-ву бит, которе занимает 1 пиксель
//        и делит на кол-во пикселей в одном байте
        padding = (3 * (bmpIh->biWidth + (4 - bmpIh->biWidth % 4)) / 4) % 4;
>>>>>>> 808fd3991398fa8c51bc8972685c9cda1d9dcd61
    } else if (bmpIh->biBitCount == 1) {
        padding = (3 * (bmpIh->biWidth + (8 - bmpIh->biWidth % 8)) / 8) % 4;
    }

//    Считывает файл побитово и в зависимости от формата bmp
//    разделяет байт на нужное кол-во пикселей
    for (int i = bmpIh->biHeight - 1; i >= 0; i--) {
        for (int j = 0; j < bmpIh->biWidth; j++) {
            fread(&bytePxl, 1, 1, *f);

            if (bmpIh->biBitCount == 8) {
                *pxA[i][j] = plt[bytePxl];
            } else if (bmpIh->biBitCount == 4) {
                *pxA[i][j] = plt[bytePxl >> 4];
                if (j + 1 < bmpIh->biWidth) {
                    *pxA[i][j + 1] = plt[bytePxl & 15];
                }
            } else if (bmpIh->biBitCount == 2) {
                for (int k = 0; k < 4 && j + k < bmpIh->biWidth; k++) {
                    *pxA[i][j + k] = plt[(bytePxl >> (6 - k * 2)) & 3];
                }
            } else {
                for (int k = 0; k < 8 && j + k < bmpIh->biWidth; k++) {
                    *pxA[i][j + k] = plt[(bytePxl >> (7 - k)) & 1];
                }
            }
        }
        fseek(*f, padding, SEEK_CUR);
    }
}

//Считывает пиксельные данные без палитры
void readNoPaletteArray(FILE **f, bitMapInfoHeader *bmpIh, pxl ***pxA) {
    WORD pixl;

    for (int i = bmpIh->biHeight - 1; i >= 0; i--) {
        for (int j = 0; j < bmpIh->biWidth; j++) {
            if (bmpIh->biBitCount >= 24) {
                if (bmpIh->biBitCount == 32) {
//                    Пропускает alpha-канал у 32-битных bmp
                    fseek(*f, 1, SEEK_CUR);
                }
                fread(&(*pxA)[i][j], 1, 3, *f);
            } else {
//                Считывает 16-битовый bmp и переводим цвет в формат 256
                fread(&pixl, 1, 2, *f);
                (*pxA)[i][j].b = (pixl & 31) * 255 / 31.0;
                (*pxA)[i][j].g = ((pixl >> 5) & 31) * 255 / 31.0;
                (*pxA)[i][j].r = ((pixl >> 10) & 31) * 255 / 31.0;
            }
        }
//        Пропускает padding
        if (bmpIh->biBitCount == 24) {
            fseek(*f, (3 * bmpIh->biWidth) % 4, SEEK_CUR);
        } else if (bmpIh->biBitCount == 16) {
            fseek(*f, (2 * bmpIh->biWidth) % 4, SEEK_CUR);
        }
    }
}

//Считывает пиксельные данные (и определят есть ли в файле палитра)
void readPixelArray(FILE **f, bitMapFileHeader *bmpFh, bitMapInfoHeader *bmpIh, pxl ***pxA) {
    pxl plt[256] = {{0, 0, 0}};

//    Считвает палитру
    if (bmpIh->biBitCount <= 8) {
        fseek(*f, bmpIh->biSize + 14, SEEK_SET);
        for (int i = 0; i < 1 << bmpIh->biBitCount; i++) {
            if (fread(plt + i, 1, 3, *f) != 3) {
                break;
            }
//            Пропускает alpha-канал
            fseek(*f, 1, SEEK_CUR);
        }
    }

    fseek(*f, bmpFh->bfOffBits, SEEK_SET);
    if (bmpIh->biBitCount <= 8) {
        readPaletteArray(f, bmpIh, plt, pxA);
    }
    if (bmpIh->biBitCount > 8) {
        readNoPaletteArray(f, bmpIh, pxA);
    }
}

//Считывает bmp
BYTE readBitMap(char *in_name, bitMapFileHeader *bmpFh, bitMapInfoHeader *bmpIh, pxl ***pxA) {
    FILE *f = fopen(in_name, "rb");
    if (f == NULL) {
        return 0;
    }
//    Считывает header файла
    readFileHeader(f, bmpFh);
    readInfoHeader(f, bmpIh);

//    Выделяет память для хранения данных пикселей
    if ((*pxA = (pxl **) malloc(bmpIh->biHeight * sizeof(pxl *))) == NULL) {
        return 0;
    }
    for (int i = 0; i < bmpIh->biHeight; i++) {
        if ((*pxA[i] = malloc(bmpIh->biWidth * sizeof(pxl))) == NULL) {
            return 0;
        }
    }
//    Считывает пиксельное поле
    readPixelArray(&f, bmpFh, bmpIh, pxA);
    if (f != NULL) {
        fclose(f);
    }
    return 1;
}

//Пиксель rgba для записи в файл
void stCol(p_pxl *pxl, BYTE r, BYTE g, BYTE b, BYTE a) {
    pxl->r = r;
    pxl->g = g;
    pxl->b = b;
    pxl->a = a;
}

//Обновляет и записывает FileHeader и InfoHeader в файл
void writeHead(FILE *f, bitMapFileHeader bmpFh, bitMapInfoHeader bmpIh) {
//    f = fopen(out_name, "wb");

//    Записывает данные в header
    bmpFh.bfOffBits = sizeof(bitMapFileHeader) + sizeof(bitMapInfoHeader) + 256 * sizeof(p_pxl);
    bmpFh.bfSize =
            bmpFh.bfOffBits + bmpIh.biWidth * bmpIh.biHeight * sizeof(BYTE) + (3 * bmpIh.biWidth) % 4 * sizeof(BYTE);
    bmpIh.biBitCount = 8;

//    Записывает FileHeader в файл
    fwrite(&bmpFh.bfType, 2, 1, f);
    fwrite(&bmpFh.bfSize, 4, 1, f);
    fwrite(&bmpFh.bfReserved1, 2, 1, f);
    fwrite(&bmpFh.bfReserved2, 2, 1, f);
    fwrite(&bmpFh.bfOffBits, 4, 1, f);

//    Записывает InfoHeader в файл
    fwrite(&bmpIh.biSize, 4, 1, f);
    fwrite(&bmpIh.biWidth, 4, 1, f);
    fwrite(&bmpIh.biHeight, 4, 1, f);
    fwrite(&bmpIh.biPlanes, 2, 1, f);
    fwrite(&bmpIh.biBitCount, 2, 1, f);
    fwrite(&bmpIh.biCompression, 4, 1, f);
    fwrite(&bmpIh.biSizeImage, 4, 1, f);
    fwrite(&bmpIh.biXPelsPerMeter, 4, 1, f);
    fwrite(&bmpIh.biYPelsPerMeter, 4, 1, f);
    fwrite(&bmpIh.biClrUsed, 4, 1, f);
    fwrite(&bmpIh.biClrImportant, 4, 1, f);
}

//Записывает пиксельные данные (8-битный bmp)
void writePixelArray(FILE *f, bitMapInfoHeader *bmpIh, pxl **pxA) {
    int padding = (3 * bmpIh->biWidth) % 4;
    BYTE bytePxl;

    for (int i = bmpIh->biHeight - 1; i >= 0; i--) {
        bytePxl = 0;
        for (int j = 0; j < bmpIh->biWidth; j++) {
            bytePxl = ((BYTE) (pxA[i][j].r + pxA[i][j].g + pxA[i][j].b) / 3.0);
            fwrite(&bytePxl, 1, 1, f);
        }
        bytePxl = 0;
        for (int k = 0; k < padding; k++) {
            fwrite(&bytePxl, 1, 1, f);
        }
    }
}

//Записывает монохромное 8-битное изображение
void writeBitMap(char *out_name, bitMapFileHeader *bmpFh, bitMapInfoHeader *bmpIh, pxl **pxA) {
    FILE *f = fopen(out_name, "wb");
    p_pxl place;
    writeHead(f, *bmpFh, *bmpIh);

//    Записывает палитру
    for (BYTE i = 0; i < 256; i++) {
        stCol(&place, i, i, i, 0);
        fwrite(&place, 1, 4, f);
    }

//    Записывает пиксельные данные
    writePixelArray(f, bmpIh, pxA);
    fclose(f);

}

//Освобождает память, выделенную под пикскльные данные
void freePixelArray(bitMapInfoHeader *bmpIh, pxl ***pxA) {
    if (pxA != NULL && *pxA != NULL) {
        for (int i = 0; i < bmpIh->biHeight; i++) {
            free((*pxA)[i]);
        }
        free(*pxA);
    }
}

int main(int argc, char *argv[]) {
//    BmpToGrey("input.bmp");
    bitMapFileHeader bmpFh;
    bitMapInfoHeader bmpIh;
    pxl **pxA = NULL;

    char out_file_name[PATH_LEN] = "output.bmp", in_file_name[PATH_LEN] = "input.bmp";
//    Проверяет наличие параметров
    for (int i = 0; i < argc; i++) {
        if (strstr(argv[i], "--input=") != NULL) {
            in_file_name[0] = '\0';
            strcat(in_file_name, argv[i] + strlen("--input="));
        } else if (strstr(argv[i], "--output=") != NULL) {
            out_file_name[0] = '\0';
            strcat(out_file_name, argv[i] + strlen("--output="));
        }
    }

    if (!readBitMap(in_file_name, &bmpFh, &bmpIh, &pxA)) {
        freePixelArray(&bmpIh, &pxA);
        return 1;
    }

    writeBitMap(out_file_name, &bmpFh, &bmpIh, pxA);
    freePixelArray(&bmpIh, &pxA);

    return 0;
}
