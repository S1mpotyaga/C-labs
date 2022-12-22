#include "bmp.h"
#include "stego.h"
#include <string.h>
#include <stdlib.h>

bool checkAtoi(int32_t value, char* str) {
	if (value == 0) return (strcmp(str, "0") == 0);
	return true;
}

static int FAILED = -1;

static int cropRotate(char* fileIn, char* fileOut, 
	int32_t x, int32_t y, int32_t w, int32_t h) {

	BMPImage* inputImage = malloc(sizeof(BMPImage));
	BMPExtraInfo* inputExtraInfo = malloc(sizeof(BMPExtraInfo));

	if (!load_bmp(fileIn, inputImage, inputExtraInfo)) {
		freeBmp(inputImage, inputExtraInfo);
		return FAILED;
	}

	y = inputImage->header.heightPx - y - h;

	BMPImage* croppedImage = malloc(sizeof(BMPImage));
	BMPExtraInfo* croppedExtraInfo = malloc(sizeof(BMPExtraInfo));


	if (!crop(inputImage, inputExtraInfo, x, y, w, h, 
			  croppedImage, croppedExtraInfo)) {
		freeBmp(inputImage, inputExtraInfo);
		freeBmp(croppedImage, croppedExtraInfo);
		return FAILED;
	}

	BMPImage* rotatedImage = malloc(sizeof(BMPImage));
	BMPExtraInfo* rotatedExtraInfo = malloc(sizeof(BMPExtraInfo));

	if (!rotate(croppedImage, croppedExtraInfo, rotatedImage, rotatedExtraInfo)) {
		freeBmp(inputImage, inputExtraInfo);
		freeBmp(croppedImage, croppedExtraInfo);
		freeBmp(rotatedImage, rotatedExtraInfo);
		return FAILED;
	}

	if (!save_bmp(fileOut, rotatedImage)) {
		freeBmp(inputImage, inputExtraInfo);
		freeBmp(croppedImage, croppedExtraInfo);
		freeBmp(rotatedImage, rotatedExtraInfo);
		return FAILED;
	}

	freeBmp(inputImage, inputExtraInfo);
	freeBmp(croppedImage, croppedExtraInfo);
	freeBmp(rotatedImage, rotatedExtraInfo);
	return 0;
}

static int insert(char* fileIn, char* fileOut, char* keyTxt, char* msgTxt) {
	BMPImage* inputImage = malloc(sizeof(BMPImage));
	BMPExtraInfo* inputExtraInfo = malloc(sizeof(BMPExtraInfo));

	if (!load_bmp(fileIn, inputImage, inputExtraInfo)) {
		freeBmp(inputImage, inputExtraInfo);
		return FAILED;
	}

	BMPImage* result = malloc(sizeof(BMPImage));
	BMPExtraInfo* resultExtraInfo = malloc(sizeof(BMPExtraInfo));

	if (!insertText(inputImage, inputExtraInfo, keyTxt, msgTxt,
		result, resultExtraInfo))
	{
		freeBmp(inputImage, inputExtraInfo);
		freeBmp(result, resultExtraInfo);
	}

	if (!save_bmp(fileOut, result)) {
		freeBmp(inputImage, inputExtraInfo);
		freeBmp(result, resultExtraInfo);
		return FAILED;
	}
	
	freeBmp(inputImage, inputExtraInfo);
	freeBmp(result, resultExtraInfo);

	return 0;
}

static int extract(char* fileIn, char* keyTxt, char* msgTxt) {
	BMPImage* image = malloc(sizeof(BMPImage));
	BMPExtraInfo* extraInfo = malloc(sizeof(BMPExtraInfo));

	if (!load_bmp(fileIn, image, extraInfo)) {
		freeBmp(image, extraInfo);
		return FAILED;
	}

	if (!extractText(image, extraInfo, keyTxt, msgTxt)) {
		freeBmp(image, extraInfo);
		return FAILED;
	}
	freeBmp(image, extraInfo);
	return 0;
}

int main(int argc, char** argv) {
	
	const int ARGC_CROP_ROTATE = 8;
	const int ARGC_INSERT = 6;
	const int ARGC_EXTRACT = 5;

	const char* MODE_CROP_ROTATE = "crop-rotate";
	const char* MODE_INSERT = "insert";
	const char* MODE_EXTRACT = "extract";

	if (argc != ARGC_CROP_ROTATE && argc != ARGC_INSERT && argc != ARGC_EXTRACT) {
		return FAILED;
	}

	char* mode = argv[1];
	if (argc == ARGC_CROP_ROTATE) {
		if (strcmp(mode, MODE_CROP_ROTATE) != 0) return FAILED;

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
			return FAILED;
		}

		return cropRotate(fileIn, fileOut, x, y, w, h);
	} else if (argc == ARGC_INSERT) {
		if (strcmp(mode, MODE_INSERT) != 0) return FAILED;

		char* fileIn = argv[2];
		char* fileOut = argv[3];
		char* keyTxt = argv[4];
		char* msgTxt = argv[5];

		int res = insert(fileIn, fileOut, keyTxt, msgTxt);

		return res;
	} else if (argc == ARGC_EXTRACT) {
		if (strcmp(mode, MODE_EXTRACT) != 0) return FAILED;
		char* fileIn = argv[2];
		char* keyTxt = argv[3];
		char* msgTxt = argv[4];

		int res = extract(fileIn, keyTxt, msgTxt);
		return res;
	} else {
		return FAILED;
	}

	return 0;
}