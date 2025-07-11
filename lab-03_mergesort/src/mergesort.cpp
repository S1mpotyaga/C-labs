#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void copy(void* src, size_t count, void* dest){
	char* itFrom = (char*) src;
	char* itRes = (char*) dest;
	for (size_t i = 0; i < count; ++i){
		*itRes = *itFrom;
		itRes++;
		itFrom++;
	}
}

int mergesort(
	void* array,
	size_t elements, size_t element_size,
	int (*comparator)(const void*, const void*)
){
	if (elements <= 1){
		return 0;
	}
	size_t leftElements = elements / 2;
	size_t rightElements = elements - leftElements;
	void* itLeft = array;
	void* itRight = (char*)array + leftElements * element_size;
	if (mergesort(itLeft, leftElements, element_size, comparator) != 0){
		return -1;
	}
	if (mergesort(itRight, rightElements, element_size, comparator) != 0){
		return -1;
	}
	void* result = malloc(elements * element_size);
	void* itLeftEnd = (char*)array + leftElements * element_size;
	void* itRightEnd = (char*)array + elements * element_size;
	while ((itLeft != itLeftEnd) || (itRight != itRightEnd)){
		if ((itLeft != itLeftEnd) && (itRight != itRightEnd)){
			if (comparator(itLeft, result) < 0){
				copy(itLeft, element_size, result);
				itLeft = (char*)itLeft + element_size;
			} else{
				copy(itRight, element_size, result);
				itRight = (char*)itRight + element_size;
			}
		} else if (itLeft != itLeftEnd){
			copy(itLeft, element_size, result);
			itLeft = (char*)itLeft + element_size;
		} else if (itRight != itRightEnd){
			copy(itRight, element_size, result);
			itRight = (char*)itRight + element_size;
		}
		result = (char*)result + element_size;
	}
	copy(result, elements, array);
	free(result);
	return 0;
}