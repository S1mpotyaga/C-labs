#include "bmp.h"
#include <string.h>
#include <stdlib.h>

bool checkAtoi(int32_t value, char* str) {
	if (value == 0) return (strcmp(str, "0") == 0);
	return true;
}

int main(int argc, char** argv) {
	const int ARGC = 8;
	const char* MODE = "crop-rotate";


	if (argc != ARGC) {
		printf("Incorrect count of params: %i, but needs %i\n", argc, ARGC);
		return 0;
	}
	char* mode = argv[1];
	char* fileIn = argv[2];
	char* fileOut = argv[3];

	int32_t x = atoi(argv[4]);
	int32_t y = atoi(argv[5]);
	int32_t w = atoi(argv[6]);
	int32_t h = atoi(argv[7]);

	if (!checkAtoi(x, argv[4]) ||
		!checkAtoi(y, argv[5]) ||
		!checkAtoi(w, argv[6]) ||
		!checkAtoi(h, argv[7]))
	{
		printf("Incorrect coords\n");
		return 0;
	}

	if (strcmp(mode, MODE) != 0) {
		printf("Incorrect mode: %s, but needs %s\n", mode, MODE);
		return 0;
	}

	BMPImage* inputImage = malloc(sizeof(BMPImage));
	BMPExtraInfo* inputExtraInfo = malloc(sizeof(BMPExtraInfo));

	char* error = NULL;

	error = load_bmp(fileIn, inputImage, inputExtraInfo);
	if (error != NULL) {
		printf("%s\n", error);
		return 0;
	}

	y = inputImage->header.heightPx - y - h;

	BMPImage* croppedImage = malloc(sizeof(BMPImage));
	BMPExtraInfo* croppedExtraInfo = malloc(sizeof(BMPExtraInfo));

	error = crop(inputImage, inputExtraInfo, x, y, w, h, croppedImage, croppedExtraInfo);

	if (error != NULL) {
		printf("%s\n", error);

		freeBmp(inputImage, inputExtraInfo);
		freeBmp(croppedImage, croppedExtraInfo);
		return 0;
	}

	BMPImage* rotatedImage = malloc(sizeof(BMPImage));
	BMPExtraInfo* rotatedExtraInfo = malloc(sizeof(BMPExtraInfo));

	error = rotate(croppedImage, rotatedImage, rotatedExtraInfo);
	if (error != NULL) {
		printf("%s\n", error);

		freeBmp(inputImage, inputExtraInfo);
		freeBmp(croppedImage, croppedExtraInfo);
		freeBmp(rotatedImage, rotatedExtraInfo);
		return 0;
	}

	save_bmp(fileOut, rotatedImage);

	freeBmp(inputImage, inputExtraInfo);
	freeBmp(croppedImage, croppedExtraInfo);
	freeBmp(rotatedImage, rotatedExtraInfo);
	return 0;
}