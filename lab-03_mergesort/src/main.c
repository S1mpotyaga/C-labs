#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/mergesort.h"

int comporator_int(const void* a, const void* b){
	return *(int*)a - *(int*)b;
}

int comporator_char(const void* a, const void* b){
	return *(char*)a - *(char*)b;
}

int comporator_str(const void* a, const void* b){
	return strcmp(*(char**)a, *(char**)b);
}

int main(int argc, char* argv[]){
	size_t n = argc - 2;
	if (strcmp(argv[1], "int") == 0){
		int a[n];
		for (size_t i = 0; i < n; ++i){
			a[i] = atoi(argv[i + 2]);
		}
		if (mergesort(a, n, sizeof(a[0]), comporator_int) != 0){
			printf("Error: memory allocation failed.");
			return 0;
		}
		for (size_t i = 0; i < n; ++i){
			printf("%d", a[i]);
			if (i != n - 1){
				printf(" ");
			}
		}
	} else if (strcmp(argv[1], "char") == 0){
		char a[n];
		for (size_t i = 0; i < n; ++i){
			a[i] = argv[i + 2][0];
		}
		if (mergesort(a, n, sizeof(a[0]), comporator_char) != 0){
			printf("Error: memory allocation failed.");
			return 0;
		}
		for (size_t i = 0; i < n; ++i){
			printf("%c", a[i]);
			if (i != n - 1){
				printf(" ");
			}
		}
	} else if (strcmp(argv[1], "str") == 0){
		char* a[n];
		for (size_t i = 0; i < n; ++i){
			a[i] = argv[i + 2];
		}
		if (mergesort(a, n, sizeof(a[0]), comporator_str) != 0){
			printf("Error: memory allocation failed.");
			return 0;
		}
		for (size_t i = 0; i < n; ++i){
			printf("%s", a[i]);
			if (i != n - 1){
				printf(" ");
			}
		}
	}
	printf("\n");
	return 0;
}