#include "mergesort.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

int int_comparator(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

int char_comparator(const void* a, const void* b) {
	return *(char*)a - *(char*)b;
}

int str_comparator(const void* a, const void* b) {
	// printf("first %s second %s, result %d\n", (char*)a, (char*) b, strcmp((char*)a, (char*)b));
	return strcmp(*((char**)a), *((char**)b));
}

int main(int argc, char* argv[]) {
	size_t n = argc - 2;
	if (strcmp(argv[1], "int") == 0) {
		int a[n];
		for (size_t i = 0; i < n; i++) a[i] = atoi(argv[i + 2]);

		if (
		mergesort(a, n, sizeof a[0], int_comparator) != 0) {
			printf("Error: memory allocation failed");
			return 0;
		}
		
		for (size_t i = 0; i < n; i++) {
			printf("%d", a[i]);
			if (i != n - 1) printf(" ");
		}
	} else if (strcmp(argv[1], "char") == 0){
		char a[n];
		for (size_t i = 0; i < n; i++) a[i] = argv[i + 2][0];

		if (
			mergesort(a, n, sizeof a[0], char_comparator) != 0) {
			printf("Error: memory allocation failed");
			return 0;
		}
		
		for (size_t i = 0; i < n; i++) {
			printf("%c", a[i]);
			if (i != n - 1) printf(" ");
		}
	} else if (strcmp(argv[1], "str") == 0){
		char* a[n];
		for (size_t i = 0; i < n; i++) a[i] = argv[i + 2];

		// for (size_t i = 0; i < n; i++) {
		// 	for (size_t j = 0; j < n; j++) {
		// 		printf("cmp of str %zu and %zu is %d\n", i, j, str_comparator(a[i], a[j]));
		// 	}
		// }

		if (
			mergesort(a, n, sizeof a[0], str_comparator) != 0) {
			printf("Error: memory allocation failed");
			return 0;
		}
		
		for (size_t i = 0; i < n; i++) {
			printf("%s", a[i]);
			if (i != n - 1) printf(" ");
		}
	}
	printf("\n");
	return 0;
}