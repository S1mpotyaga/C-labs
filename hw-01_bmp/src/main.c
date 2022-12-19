#include "bmp.h"
#include <string.h>
#include <stdlib.h>

bool checkAtoi(int32_t value, char* str) {
	if (value == 0) return (strcmp(str, "0") == 0);
	return true;
}

int main(int argc, char** argv) {
	const int FAILED_MAIN = -1;
	const int ARGC = 8;
	const char* MODE = "crop-rotate";


	if (argc != ARGC) {
		printf("Incorrect count of params: %i, but needs %i\n", argc, ARGC);
		return FAILED_MAIN;
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
		#ifdef LOCAL
			printf("Incorrect coords\n");
		#endif
		return FAILED_MAIN;
	}

	if (strcmp(mode, MODE) != 0) {
		#ifdef LOCAL
			printf("Incorrect mode: %s, but needs %s\n", mode, MODE);
		#endif
		return FAILED_MAIN;
	}

	BMPImage* inputImage = malloc(sizeof(BMPImage));
	BMPExtraInfo* inputExtraInfo = malloc(sizeof(BMPExtraInfo));

	char* error = NULL;

	if (!load_bmp(fileIn, inputImage, inputExtraInfo)) {
		printf("error\n");
		freeBmp(inputImage, inputExtraInfo);
		return FAILED_MAIN;
	}

	y = inputImage->header.heightPx - y - h;

	BMPImage* croppedImage = malloc(sizeof(BMPImage));
	BMPExtraInfo* croppedExtraInfo = malloc(sizeof(BMPExtraInfo));


	error = crop(inputImage, inputExtraInfo, x, y, w, h, croppedImage, croppedExtraInfo);

	if (error != NULL) {
		#ifdef LOCAL
			printf("crop error: %s\n", error);
		#endif
		freeBmp(inputImage, inputExtraInfo);
		freeBmp(croppedImage, croppedExtraInfo);
		free(error);
		return FAILED_MAIN;
	}

	BMPImage* rotatedImage = malloc(sizeof(BMPImage));
	BMPExtraInfo* rotatedExtraInfo = malloc(sizeof(BMPExtraInfo));

	error = rotate(croppedImage, rotatedImage, rotatedExtraInfo);
	if (error != NULL) {
		#ifdef LOCAL
			printf("rotate error: %s\n", error);
		#endif
		freeBmp(inputImage, inputExtraInfo);
		freeBmp(croppedImage, croppedExtraInfo);
		freeBmp(rotatedImage, rotatedExtraInfo);
		free(error);
		free(fileIn);
		free(fileOut);
		return FAILED_MAIN;
	}

	if (!save_bmp(fileOut, rotatedImage)) {
		freeBmp(inputImage, inputExtraInfo);
		freeBmp(croppedImage, croppedExtraInfo);
		freeBmp(rotatedImage, rotatedExtraInfo);
		return FAILED_MAIN;
	}

	freeBmp(inputImage, inputExtraInfo);
	freeBmp(croppedImage, croppedExtraInfo);
	freeBmp(rotatedImage, rotatedExtraInfo);
	return 0;
}