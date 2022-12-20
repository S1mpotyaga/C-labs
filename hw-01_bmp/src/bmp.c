#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>

#define MAGIC_VALUE 0x4D42 
#define NUM_COLOR_PLANES 1
#define COMPRESSION_TYPE 0
#define NUM_COLORS 0
#define IMPORTANT_COLORS 0
#define BITS_PER_PIXEL 24
#define BITS_PER_BYTE 8

#define BMP_HEADER_SIZE 54
#define DIB_HEADER_SIZE_BYTES 40

long getFileSize(FILE* file) {
    long currentPos = ftell(file);
    if (currentPos == -1) return -1;

    if (fseek(file, 0, SEEK_END) != 0) return -2;

    long fileSize = ftell(file);
    if (fileSize == -1) return -3;

    if (fseek(file, currentPos, SEEK_SET) != 0) return -4;

    return fileSize;
}

void calcBytesPerPixel(BMPHeader* header, BMPExtraInfo* extraInfo) {
    extraInfo->bytesPerPixel = header->bitsPerPixel / BITS_PER_BYTE;
}

void calcPadding(BMPHeader* header, BMPExtraInfo* extraInfo) {
    extraInfo->padding = (4 - (header->widthPx * extraInfo->bytesPerPixel) % 4) % 4;
}

void calcRowSizeBytes(BMPHeader* header, BMPExtraInfo* extraInfo) {
    int bytesPerRowWithoutPadding = header->widthPx * extraInfo->bytesPerPixel;
    extraInfo->rowSizeBytes = bytesPerRowWithoutPadding + extraInfo->padding;
}

void caclImageSizeBytes(BMPHeader* header, BMPExtraInfo* extraInfo) {
    extraInfo->imageSizeBytes = extraInfo->rowSizeBytes * header->heightPx;
}

void calcFileSizeBytes(long fileSize, BMPExtraInfo* extraInfo) {
    extraInfo->fileSizeBytes = fileSize;
}

void calcAllAboutHeader(BMPHeader* header, BMPExtraInfo* extraInfo) {
    calcBytesPerPixel(header, extraInfo);
    calcPadding(header, extraInfo);
    calcRowSizeBytes(header, extraInfo);
    caclImageSizeBytes(header, extraInfo);
}

void calcExtraInfo(BMPHeader* header, long fileSize, BMPExtraInfo* extraInfo) {
    calcAllAboutHeader(header, extraInfo);
    calcFileSizeBytes(fileSize, extraInfo);
}

bool readHeader(FILE* file, BMPHeader* header) {
    rewind(file);
    if (fread(header, sizeof(BMPHeader), 1, file) != 1) 
        return false;
    return true;
}

bool checkHeader(BMPHeader* header, 
                 BMPExtraInfo* extraInfo) {
    return
        header->type == MAGIC_VALUE
        && header->offsetImageData == BMP_HEADER_SIZE
        && header->dibHeaderSizeBytes == DIB_HEADER_SIZE_BYTES
        && header->numColorPlanes == NUM_COLOR_PLANES
        && header->compressionType == COMPRESSION_TYPE
        && header->numColors == NUM_COLORS
        && header->importantColors == IMPORTANT_COLORS
        && header->bitsPerPixel == BITS_PER_PIXEL
        && header->fileSizeBytes == extraInfo->fileSizeBytes
        && header->imageSizeBytes == extraInfo->imageSizeBytes
        ;
}



 
bool load_bmp(char *filename, BMPImage* image, BMPExtraInfo* extraInfo) {

    image->data = NULL;
    FILE* file = fopen(filename, "rb");
    
    if (file == NULL) {
        fclose(file);
        return false;
    }

    if (!readHeader(file, &(image->header))) {
        fclose(file);
        return false;
    }


    calcExtraInfo(&image->header, getFileSize(file), extraInfo);
    
    if (!checkHeader(&image->header, extraInfo)) {
        fclose(file);
        return false;
    }

    image->data = malloc(image->header.imageSizeBytes);
    if (image->data == NULL) {
        return false;
    }

    if(fread(image->data, image->header.imageSizeBytes, 1, file) != 1) {
        fclose(file);
        return false;
    }
    
    fclose(file);
    return true;
}

bool save_bmp(char* filename, BMPImage* image) {
    FILE* out = fopen(filename, "wb");

    if (fwrite(&(image->header), sizeof(BMPHeader), 1, out) != 1) {
        fclose(out);
        return false;
    }

    if (fwrite(image->data, image->header.imageSizeBytes, 1, out) != 1) {
        fclose(out);
        return false;
    }

    fclose(out);
    return true;
}

bool checkCoords(BMPHeader* header, int32_t x, int32_t y,
     int32_t w, int32_t h) {
    return 0 <= x && 0 <= y && w >= 0 && h >= 0 &&
           x + w <= header->widthPx && 
           y + h <= header->heightPx;
}

int getPositionXRow(int x, BMPExtraInfo* extraInfo)
{
    return x * extraInfo->bytesPerPixel;
}

bool crop(BMPImage* image, BMPExtraInfo* extraInfo, int32_t x, int32_t y,
           int32_t w, int32_t h, BMPImage* result,
           BMPExtraInfo* resultExtraInfo) {
    result->data = NULL;

    if (!checkCoords(&image->header, x, y, w, h))
        return false;
    result->header = image->header;
    result->header.widthPx = w;
    result->header.heightPx = h;

    calcAllAboutHeader(&result->header, resultExtraInfo);
    
    result->header.imageSizeBytes = resultExtraInfo->imageSizeBytes;
    result->header.fileSizeBytes = BMP_HEADER_SIZE + result->header.imageSizeBytes; 

    calcFileSizeBytes(result->header.fileSizeBytes, resultExtraInfo);

    result->data = malloc(sizeof(char) * result->header.imageSizeBytes);
    if (result->data == NULL) {
        return false;
    }

    int posY = y * extraInfo->rowSizeBytes;
    int posXRow = getPositionXRow(x, extraInfo);

    int index = 0;
    int padding = resultExtraInfo->padding;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int k = 0; k < 3; k++) {
                result->data[index] = image->data[posY + posXRow];
                index++;
                posXRow++;
            }
        }
        
        for (int l = 0; l < padding; l++) {
            result->data[index] = 0x00;
            index++;
        }
        posY += extraInfo->rowSizeBytes;
        posXRow = getPositionXRow(x, extraInfo);
    }

    return true;
}

bool rotate(BMPImage* image, BMPExtraInfo* imageExtraInfo,
             BMPImage* result, BMPExtraInfo* resultExtraInfo) {
    result->data = NULL;

    int w = image->header.heightPx;
    int h = image->header.widthPx;

    result->header = image->header;
    result->header.widthPx = w;
    result->header.heightPx = h;

    calcAllAboutHeader(&result->header, resultExtraInfo);
    
    result->header.imageSizeBytes = resultExtraInfo->imageSizeBytes;
    result->header.fileSizeBytes = BMP_HEADER_SIZE + resultExtraInfo->imageSizeBytes;

    calcFileSizeBytes(result->header.fileSizeBytes, resultExtraInfo);

    result->data = malloc(sizeof(char) * result->header.imageSizeBytes);    if (result->data == NULL) {
        return false;
    }
    
    int padding = resultExtraInfo->padding;

    int index = 0;

    int posX = 0, posY = 0;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            posY = j * imageExtraInfo->rowSizeBytes;
            posX = getPositionXRow(h - i - 1, imageExtraInfo);
            for (int k = 0; k < 3; k++) {

                // printf("posY %i posX %i size %i\n", posY, posX, image->header.imageSizeBytes);
                result->data[index] = image->data[posY + posX];
                index++;
                posX++;
            }
        }
        for (int l = 0; l < padding; l++) {
            result->data[index] = 0x00;
            index++;
        }
    }

    return true;
}

void freeBmp(BMPImage* image, BMPExtraInfo* extraInfo) {
    free(image->data);
    free(image);
    free(extraInfo);
}