#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#pragma pack(push)
#pragma pack(1)

struct BMPheader{
    uint16_t type;               // Magic identifier: 0x4d42
    uint32_t fileSizeBytes;
    uint16_t unused1;         
    uint16_t unused2;         
    uint32_t offsetImageData;   
    uint32_t dibHeaderSizeBytes;
    int32_t  widthPx;
    int32_t  heightPx;
    uint16_t numColorPlanes;
    uint16_t bitsPerPixel;
    uint32_t compressionType;
    uint32_t imageSizeBytes;
    int32_t  xPixelsPerMeter;
    int32_t  yPixelsPerMeter;
    uint32_t numColors;
    uint32_t importantColors;
};
typedef struct BMPheader BMPHeader;


#pragma pack(pop)

struct BMPimage {
    BMPHeader header;
    unsigned char* data;
};
typedef struct BMPimage BMPImage;


struct BMPextraInfo{
    uint32_t imageSizeBytes;
    uint32_t rowSizeBytes;
    uint32_t bytesPerPixel;
    uint32_t padding;

    uint32_t fileSizeBytes;
};
typedef struct BMPextraInfo BMPExtraInfo;


 
bool load_bmp(char *filename, BMPImage* image, BMPExtraInfo* info);
 
bool crop(BMPImage* image, BMPExtraInfo* extraInfo, int32_t x, int32_t y,
           int32_t w, int32_t h, BMPImage* result,
           BMPExtraInfo* resultExtraInfo);
 
bool rotate(BMPImage* image, BMPExtraInfo* imageExtraInfo,
             BMPImage* result, BMPExtraInfo* resultExtraInfo);
 
bool save_bmp(char* filename, BMPImage* image);

void freeBmp(BMPImage* image, BMPExtraInfo* extraInfo);

bool copyBMP(BMPImage* image, BMPExtraInfo* imageExtraInfo,
             BMPImage* result, BMPExtraInfo* resultExtraInfo);

void calcAllAboutHeader(BMPHeader* header, BMPExtraInfo* extraInfo);

void calcExtraInfo(BMPHeader* header, long fileSize, BMPExtraInfo* extraInfo);

void calcFileSizeBytes(long fileSize, BMPExtraInfo* extraInfo);

int getPositionXRow(int x, BMPExtraInfo* extraInfo);

bool checkCoords(BMPHeader* header, int32_t x, int32_t y,
     int32_t w, int32_t h);

 