#include "point_list.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

const int BITE_COUNT = 3;

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
	fwrite(&(p->x), 3, 1, f);
	fwrite(&(p->y), 3, 1, f);
}

int main(int argc, char* argv[]) {

	const int MAXN = 1000;

	if (argc < 4) {
		printf("Incorrect params count\n");
		return 0;
	}

	char* fileType = argv[1];
	char* inFile = argv[2];
	char* action = argv[3];

	FILE *fIn = NULL;

	int x[MAXN];
	int y[MAXN];
	int cntPoints = 0;

	if (strcmp(fileType, "loadtext") == 0) {
		fIn = fopen(inFile, "r");

		while(fscanf(fIn, "%d %d", &x[cntPoints], &y[cntPoints]) != EOF) {
			cntPoints++;
		}
	} else if(strcmp(fileType, "loadbin") == 0) {
		fIn = fopen(inFile, "rb");

		while (fread(&x[cntPoints], BITE_COUNT, 1, fIn) == 1 && 
				fread(&y[cntPoints], BITE_COUNT, 1, fIn) == 1)
		{
			cntPoints++;
		}
	} else {
		printf("Incorrect output filetype\n");
		fclose(fIn);
		return 0;
	}

	fclose(fIn);

	struct intrusive_list* l = malloc(sizeof(struct intrusive_list));
	init_list(l);

	for (int i = cntPoints - 1; i >= 0; i--) {
		add_point(l, x[i], y[i]);
	}

	if (strcmp(action, "print") == 0) {
		char* formatString = argv[4];
		apply(l, printElem, formatString);
		printf("\n");
	} else if (strcmp(action, "count") == 0) {
		int count = 0;
		apply(l, countElem, &count);
		printf("%d\n", count);	
	} else {
		if (argc < 5) {
			printf("Incorrect count of params\n");
			return 0;
		}
		FILE* fOut = NULL;
		if (strcmp(action, "savetext") == 0) {
			char* outFile = argv[4];
			fOut = fopen(outFile, "w");
			apply(l, saveText, fOut);
		} else if (strcmp(action, "savebin") == 0) {
			char* outFile = argv[4];
			fOut = fopen(outFile, "wb");
			apply(l, saveBin, fOut);
		} else {
			printf("Incorrect out file\n");
			fclose(fOut);
			return 0;
		}

		fclose(fOut);
	}
	remove_all_points(l);
	deinit_list(l);

	return 0;
}