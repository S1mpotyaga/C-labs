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
	size_t count_args = argc - 2;
    if (argc < 2){
        printf("Error: invalid input data.\n");
        fflush(stdout);
        return 0;
    }
    int return_code = 0;
	if (strcmp(argv[1], "int") == 0){
		int *array = malloc(count_args * sizeof(int));
        if (array == NULL){
            printf("Error: memory allocation failed.");
            fflush(stdout);
            return 1;
        }
		for (size_t i = 0; i < count_args; ++i){
			array[i] = atoi(argv[i + 2]);
			if (array[i] == 0 && strcmp(argv[i + 2],  "0") != 0) {
			    printf("Argument number %zu is incorrect: '%s' is not a number", i + 1, argv[i + 2]);
                fflush(stdout);
                free(array);
                return 0;
            }
		}
        int mergesort_return_code = mergesort(array, count_args, sizeof(array[0]), comporator_int);
		if (mergesort_return_code == 0){
    		for (size_t i = 0; i < count_args; ++i){
	    		printf("%d", array[i]);
		    	if (i != count_args - 1){
				    printf(" ");
			    }
		    }
        }else if (mergesort_return_code == -1){
            printf("Error: memory allocation failed.");
            fflush(stdout);
            return_code = 1;
        } else {
            printf("Undefined mergesort error code: %d", mergesort_return_code);
            fflush(stdout);
            return_code = 1;
        }
        free(array);
	} else if (strcmp(argv[1], "char") == 0){
		char *array = malloc(count_args * sizeof(char));
        if (array == NULL){
            printf("Error: memory allocation failed.");
            return 1;
        }
		for (size_t i = 0; i < count_args; ++i){
			array[i] = argv[i + 2][0];
		}
		int mergesort_return_code = mergesort(array, count_args, sizeof(array[0]), comporator_char);
		if (mergesort_return_code == 0){
    		for (size_t i = 0; i < count_args; ++i){
	    		printf("%c", array[i]);
		    	if (i != count_args - 1){
				    printf(" ");
			    }
		    }
        }else if (mergesort_return_code == -1){
            printf("Error: memory allocation failed.");
            fflush(stdout);
            return_code = 1;
        } else {
            printf("Undefined mergesort error code: %d", mergesort_return_code);
            fflush(stdout);
            return_code = 1;
        }
        free(array);
	} else if (strcmp(argv[1], "str") == 0){
		char **array = malloc(count_args * sizeof(char*));
        if (array == NULL){
            printf("Error: memory allocation failed.");
            return 1;
        }
		for (size_t i = 0; i < count_args; ++i){
			array[i] = argv[i + 2];
		}
		int mergesort_return_code = mergesort(array, count_args, sizeof(array[0]), comporator_str);
		if (mergesort_return_code == 0){
    		for (size_t i = 0; i < count_args; ++i){
	    		printf("%s", array[i]);
		    	if (i != count_args - 1){
				    printf(" ");
			    }
		    }
        }else if (mergesort_return_code == -1){
            printf("Error: memory allocation failed.");
            fflush(stdout);
            return_code = 1;
        } else {
            printf("Undefined mergesort error code: %d", mergesort_return_code);
            fflush(stdout);
            return_code = 1;
        }
        free(array);
	}
	printf("\n");
	return return_code;
}