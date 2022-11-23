#include "mergesort.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

int int_comparator(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

int char_comparator(const void* a, const void* b) {
	return (int)(*(char*)a) - (int)(*(char*)b);
}

int str_comparator(const void* a, const void* b) {
	return strcmp((char*)a, (char*) b);
}

int main(int argc, char* argv[]) {
	if (strcmp(argv[1], "int") == 0) {
		size_t n = argc - 2;
		int a[n];
		for (size_t i = 0; i < n; i++) a[i] = atoi(argv[i + 2]);

		if (
		mergesort(a, sizeof a / sizeof a[0], sizeof a[0],
			int_comparator) != 0
		) {
			printf("Error: memory allocation failed");
			return 0;
		}
		
		for (size_t i = 0; i < n; i++) {
			printf("%d", a[i]);
			if (i != n - 1) printf(" ");
		}
		printf("\n");
	} else if (strcmp(argv[1], "char") == 0){
		size_t n = argc - 2;
		char a[n];
		for (size_t i = 0; i < n; i++) a[i] = argv[i + 2][0];

		if (
			mergesort(a, sizeof a / sizeof a[0], sizeof a[0],
			char_comparator) != 0
		) {
			printf("Error: memory allocation failed");
			return 0;
		}
		
		for (size_t i = 0; i < n; i++) {
			printf("%c", a[i]);
			if (i != n - 1) printf(" ");
		}
		printf("\n");
	} else if (strcmp(argv[1], "str") == 0){
		size_t n = argc - 2;
		size_t maxLen = 0, tmp = 0;
		for (int i = 2; i < argc; i++) {
			tmp = strlen(argv[i]);
			if (tmp > maxLen) maxLen = tmp;
		}
		char a[n][maxLen + 1];
		for (size_t i = 0; i < n; i++) strcpy(a[i], argv[i + 2]);

		if (
			mergesort(a, sizeof a / sizeof a[0], sizeof a[0],
			str_comparator) != 0
		) {
			printf("Error: memory allocation failed");
			return 0;
		}
		
		for (size_t i = 0; i < n; i++) {
			printf("%s", a[i]);
			if (i != n - 1) printf(" ");
		}
		printf("\n");
	}
	return 0;
}