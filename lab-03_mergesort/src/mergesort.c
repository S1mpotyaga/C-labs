#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int mergesort(
	void* array,
	size_t elements, size_t element_size,
	int (*comparator)(const void*, const void*)
){
	if (elements < 2){
		return 0;
	}
	size_t left_elements = elements / 2;
	size_t right_elements = elements - left_elements;
    
	if (mergesort(array, left_elements, element_size, comparator) != 0){
		return -1;
	}
	if (mergesort(array + left_elements * element_size, right_elements, element_size, comparator) != 0){
		return -1;
	}
	void* temp_buffer = malloc(elements * element_size);
	if (!temp_buffer){
		return -1;
	}
    void* left_end = array + element_size * left_elements;
    void* right_end = left_end + element_size * right_elements;
    void* left_current = array;
    void* right_current = left_end;
    void* result_current = temp_buffer;
	while (left_current < left_end && right_current < right_end){
        // printf("!!! %s %s\n", (char*)left_current, (char*)right_current);
        // fflush(stdout);
		if (comparator(left_current, right_current) < 0){
			memcpy(result_current, left_current, element_size);
			left_current += element_size;
		} else{
			memcpy(result_current, right_current, element_size);
			right_current += element_size;
		}
        result_current += element_size;
	}
	while (left_current < left_end){
		memcpy(result_current, left_current, element_size);
		left_current += element_size;
		result_current += element_size;
	}
	while (right_current < right_end){
		memcpy(result_current, right_current, element_size);
		right_current += element_size;
		result_current += element_size;
	}
	memcpy(array, temp_buffer, elements * element_size);
	free(temp_buffer);
	return 0;
}