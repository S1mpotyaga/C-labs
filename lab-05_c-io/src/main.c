#include "point_list.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

const int BYTE_COUNT = 3;

void printElem(struct intrusive_node* v, void* data) {
	char* formatString = (char*) data;
	struct point* p = container_of(v, struct point, node);
	printf(formatString, p->x, p->y);
}

void countElem(struct intrusive_node* v, void* data) {
	if (v == NULL) return;
	int* count = (int*) data;
	(*count)++;
}

void saveText(struct intrusive_node* v, void* data) {
	FILE* f = (FILE*) data;
	struct point* p = container_of(v, struct point, node);
	fprintf(f, "%d %d\n", p->x, p->y);
}

void saveBin(struct intrusive_node* v, void* data) {
	FILE* f = (FILE*) data;
	struct point* p = container_of(v, struct point, node);
	fwrite(&(p->x), BYTE_COUNT, 1, f);
	fwrite(&(p->y), BYTE_COUNT, 1, f);
}

int convert(int x)
{
    if( x & 0x00800000 )
        return x | 0xff000000;

    return x;
}

int main(int argc, char* argv[]) {
	if (argc < 4) {
		printf("Incorrect params count\n");
		return 0;
	}

	char* fileType = argv[1];
	char* inFile = argv[2];
	char* action = argv[3];

	FILE *fIn = NULL;

	int x, y;


	struct intrusive_list* l = malloc(sizeof(struct intrusive_list));
	init_list(l);

	if (strcmp(fileType, "loadtext") == 0) {
		fIn = fopen(inFile, "r");

		while(fscanf(fIn, "%d %d", &x, &y) != EOF) {
			add_point(l, x, y);
		}
	} else if(strcmp(fileType, "loadbin") == 0) {
		fIn = fopen(inFile, "rb");

		while (1)
		{
			x = 0;
			y = 0;
			if (fread(&x, BYTE_COUNT, 1, fIn) == 0) break;
			if (fread(&y, BYTE_COUNT, 1, fIn) == 0) break;
			x = convert(x);
			y = convert(y);
			add_point(l, x, y);
		}
	} else {
		printf("Incorrect output filetype\n");
		fclose(fIn);
		
		remove_all_points(l);
		deinit_list(l);
		return 0;
	}

	fclose(fIn);

	if (strcmp(action, "print") == 0) {
		char* formatString = argv[4];
		apply(l, printElem, formatString);
		printf("\n");
	} else if (strcmp(action, "count") == 0) {
		int count = 0;
		apply(l, countElem, &count);
		printf("%d\n", count);	
	} else {
		FILE* fOut = NULL;
		char* outFile = argv[4];
		if (strcmp(action, "savetext") == 0) {
			fOut = fopen(outFile, "w");
			apply(l, saveText, fOut);
		} else if (strcmp(action, "savebin") == 0) {
			fOut = fopen(outFile, "wb");
			apply(l, saveBin, fOut);
		}

		fclose(fOut);
	}
	remove_all_points(l);
	deinit_list(l);
	free(l);

	return 0;
}