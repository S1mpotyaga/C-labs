#include "stego.h"
#include "bmp.h"
#include <stdlib.h>


static const int MAXP = 5;

static char getCode(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c == ' ') return 26;
    else if (c == ',') return 27;
    else if (c == '.') return 28;
    return (1 << MAXP);
}

static char decode(char c) {
    if (c >= 0 && c < 26) return 'A' + c;
    if (c == 26) return ' ';
    if (c == 27) return ',';
    if (c == 28) return '.';
    return '?';
}

bool insertText(BMPImage* image, BMPExtraInfo* imageExtraInfo, char* keyTxt,
                char* msgTxt, BMPImage* result, BMPExtraInfo* resultExtraInfo) {


	FILE* messageFile = fopen(msgTxt, "r");
	FILE* keyFile = fopen(keyTxt, "r");

    if (messageFile == NULL || keyFile == NULL){
    	fclose(messageFile);
    	fclose(keyFile);
    	return false;	
    } 

    copyBMP(image, imageExtraInfo, result, resultExtraInfo);
    
    char message;
    int x, y, posX, posY;
    char c;

    while (true) {
        if (fscanf(messageFile, "%c", &message) == 0) {
            if (fscanf(keyFile, "%i %i %c\n", &x, &y, &c) != 0) {
                fclose(messageFile);
                fclose(keyFile);
                return false;
            }
        }
        char code = getCode(message);
        if (!(code >= 0 && code < (1 << MAXP))) return false;
        for (int k = 0; k < MAXP; k++) {
            if (fscanf(keyFile, "%i %i %c", &x, &y, &c) != 3) {
                fclose(messageFile);
                fclose(keyFile);
                return true;
            }
            y = result->header.heightPx - y - 1;

            if (!checkCoords(&(result->header), x, y, 0, 0)) {
            	fclose(keyFile);
            	fclose(messageFile);
            	return false;
            }

            posY = y * resultExtraInfo->rowSizeBytes;
            posX = getPositionXRow(x, resultExtraInfo);

            if (c == 'G') posX++;
        
            else if (c == 'R') posX += 2;
            else if (c != 'B') {
                fclose(keyFile);
                fclose(messageFile);
                return false;
            }


            result->data[posX + posY] |= (code % 2);
            result->data[posX + posY] &= (code % 2);
            code /= 2;
        }
    }
    
    fclose(messageFile);
    fclose(keyFile);
    return true;
}


bool extractText(BMPImage* image, BMPExtraInfo* extraInfo, char* keyTxt, char* msgTxt) {
    FILE* keyFile = fopen(keyTxt, "r");
    FILE* messageFile = fopen(msgTxt, "w");
    
    if (keyFile == NULL || messageFile == NULL) {
    	fclose(keyFile);
    	fclose(messageFile);
    	return false;
    }

    int x, y, posX, posY;
    char message = 0;
    char c;
    char decodeMessage;

    int i = 0;
    while(fscanf(keyFile, "%i %i %c\n", &x, &y, &c) == 3) {
    	y = image->header.heightPx - y - 1;

    	if (!checkCoords(&(image->header), x, y, 0, 0)) {
    		fclose(keyFile);
    		fclose(messageFile);
    		return false;
    	}

    	posY = y * extraInfo->rowSizeBytes;
        posX = getPositionXRow(x, extraInfo);

        if (c == 'G') posX++;
    
        else if (c == 'R') posX += 2;
        else if (c != 'B') {
            fclose(keyFile);
            fclose(messageFile);
            return false;
        }	
        int temp = ((image->data[posX + posY] & 1) << i);
        message |= temp;
       	
        i++;
        if (i == 5) {
        	decodeMessage = decode(message);
        	fprintf(messageFile, "%c", decodeMessage);
        	message = 0;
        	i = 0;
        }
    }
    fclose(keyFile);
    fclose(messageFile);
    return true;
}