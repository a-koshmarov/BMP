
#include <stdio.h>
#include <malloc.h>
#include <math.h>

int width, height;

void BmpToGrey(char *filename) {
    int count = 0;
    double avg;
    int padding = 0;

// Открываем файл и проверяем его наличие
    FILE *infile;
    infile = fopen(filename, "rb");

    if (infile == NULL) {
        printf("No such file\n");
        return;
    }

    unsigned char header[54];

// Считываем header файла
    fread(header, sizeof(unsigned char), 54, infile);

// Берем размеры картинки из header'a
    width = *(int *) &header[18];
    height = *(int *) &header[22];
//    printf("%d\n", height);


// Находим отсутп в конце каждой строки
    while ((width * 3 + padding) % 4 != 0) {
        padding++;
    }
//    printf("%d\n", padding);

// Длина строки с отступом
    int width_pad = width * 3 + padding;

// Записываем header в выходной файл
    FILE *outfile;
    outfile = fopen("img.bmp", "wb");
    fwrite(header, 1, 54, outfile);

// Выделяем память на строку с отступом
    unsigned char *pixels = (unsigned char *) malloc(width_pad * sizeof(unsigned int));

// Считываем файл построчно
    for (int i = 0; i < height; i++) {
// Считываем всю строку с отступом в pixels
        fread(pixels, sizeof(unsigned char), width_pad, infile);
//        count = 0;

// Считваем каждый пиксель
        for (int j = 0; j < width * 3; j += 3) {
// Находим среднее цветовое значение пикселя
            avg = round((pixels[j] + pixels[j + 1] + pixels[j + 2]) / 3.0);
            unsigned char avgu = (unsigned char) avg;
//            printf("(%d) ", avgu);
// Присваиваем среднее значение всему пикселю
            pixels[j] = avgu;
            pixels[j + 1] = avgu;
            pixels[j + 2] = avgu;

//            count++;
        }
//        printf(" %d \n\n", count);
// Запиываем строку с отступом в выходной файл
        fwrite(pixels, sizeof(unsigned char), width_pad, outfile);
    }
//    printf("%d", count);
    fclose(infile);
    fclose(outfile);
    free(pixels);
}

int main() {
    BmpToGrey("input.bmp");
    return 0;
}