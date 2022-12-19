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

char* readHeader(FILE* file, BMPHeader* header) {
    char* error = NULL;
    rewind(file);
    if (fread(header, sizeof(BMPHeader), 1, file) != 1) 
        error = "Can't read header of the file";
    return error;
}

bool checkHeader(BMPHeader* header, 
                 BMPExtraInfo* extraInfo) {
    (void)(extraInfo);
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



 
char* load_bmp(char *filename, BMPImage* image, BMPExtraInfo* extraInfo) {
    char* error = NULL;

    FILE* file = fopen(filename, "rb");
    if (file == NULL) error = "Can't find input file";
    if (error != NULL) return error;

    error = readHeader(file, &(image->header));
    if (error != NULL) return error;

    calcExtraInfo(&image->header, getFileSize(file), extraInfo);
    
    if (!checkHeader(&image->header, extraInfo)) {
        error = "Failed check header";
        printf("%u\n", image->header.offsetImageData);
    }
    if (error != NULL) return error;

    // Allocate memory for image data
    image->data = malloc(sizeof(*image->data) * image->header.imageSizeBytes);
    if (image->data == NULL) error = "Not enought memory for data";
    if (error != NULL) return error;
    
    // Read image data
    if(fread(image->data, image->header.imageSizeBytes, 1, file) != 1)
        error = "Can't read data";
    if (error != NULL) return error;

    return error;
}

char* save_bmp(char* filename, BMPImage* image) {
    FILE* out = fopen(filename, "wb");

    rewind(out);
    if (fwrite(&(image->header), sizeof(BMPHeader), 1, out) != 1)
        return "Can't write header of image";

    if (fwrite(image->data, image->header.imageSizeBytes, 1, out) != 1) 
        return "Can't write data of file";

    return NULL;
}

bool checkCoords(BMPHeader* header, int32_t x, int32_t y,
     int32_t w, int32_t h) {
    return 0 <= x && 0 <= y && 
           x + w <= header->widthPx && 
           y + h <= header->heightPx;
}

int getPositionXRow(int x, BMPExtraInfo* extraInfo)
{
    return x * extraInfo->bytesPerPixel;
}

char* crop(BMPImage* image, BMPExtraInfo* extraInfo, int32_t x, int32_t y,
           int32_t w, int32_t h, BMPImage* result,
           BMPExtraInfo* resultExtraInfo) {
    if (!checkCoords(&image->header, x, y, w, h))
        return "Incorrect coords";
    result->header = image->header;
    result->header.widthPx = w;
    result->header.heightPx = h;

    calcAllAboutHeader(&result->header, resultExtraInfo);
    
    result->header.imageSizeBytes = resultExtraInfo->imageSizeBytes;
    result->header.fileSizeBytes = BMP_HEADER_SIZE + result->header.imageSizeBytes; 

    calcFileSizeBytes(result->header.fileSizeBytes, resultExtraInfo);

    result->data = malloc(sizeof(char) * result->header.imageSizeBytes);
    if (result->data == NULL) {
        free(resultExtraInfo);
        return "Can't alloc memory for datd of new file";
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

    return NULL;
}

char* rotate(BMPImage* image,
             BMPImage* result, BMPExtraInfo* resultExtraInfo) {


    int w = image->header.heightPx;
    int h = image->header.widthPx;

    result->header = image->header;
    result->header.widthPx = w;
    result->header.heightPx = h;

    calcAllAboutHeader(&result->header, resultExtraInfo);
    
    result->header.imageSizeBytes = resultExtraInfo->imageSizeBytes;
    result->header.fileSizeBytes = BMP_HEADER_SIZE + resultExtraInfo->imageSizeBytes;

    result->data = malloc(sizeof(char) * result->header.imageSizeBytes);
    if (result->data == NULL) {
        free(resultExtraInfo);
        return "Can't alloc memory for datd of new file";
    }
    int padding = resultExtraInfo->padding;

    int index = 0;

    int posX = 0, posY = 0;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            posY = j * resultExtraInfo->rowSizeBytes;
            posX = getPositionXRow(h - i - 1, resultExtraInfo);
            for (int k = 0; k < 3; k++) {
                result->data[index] = image->data[posY + posX];
                index++;
                posX++;
            }
        }
    }

    index = 0;
    for (int i = 0; i < w; i++) {
        index = i * (3 * h + padding) + 3 * h;

        for (int l = 0; l < padding; l++) {
            result->data[index] = 0x00;
            index++;
        }
    }

    return NULL;
}

void freeBmp(BMPImage* image, BMPExtraInfo* extraInfo) {
    free(image->data);
    free(image);
    free(extraInfo);
}