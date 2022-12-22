#pragma once

#include "bmp.h"

bool insertText(BMPImage* image, BMPExtraInfo* imageExtraInfo, char* keyTxt,
                char* msgTxt, BMPImage* result, BMPExtraInfo* extraInfo);

bool extractText(BMPImage* image, BMPExtraInfo* extraInfo, char* keyTxt, char* msgTxt);