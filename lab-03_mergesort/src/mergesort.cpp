#include <stddef.h>
#include <stdlib.h>
#include <cstring>

int mergesort(
	void* array,
	size_t elements, size_t element_size,
	int (*comparator)(const void*, const void*)
){
	if (elements < 2){
		return 0;
	}
	size_t leftElements = elements / 2;
	size_t rightElements = elements - leftElements;
	char* arrayCopy = (char*)array;
	if (mergesort(array, leftElements, element_size, comparator) != 0){
		return -1;
	}
	if (mergesort((char*)array + leftElements * element_size, rightElements, element_size, comparator) != 0){
		return -1;
	}
	void* result = malloc(elements * element_size);
	if (!result){
		return -1;
	}
	size_t indLeft = 0, indRight = leftElements, indResult = 0;
	while (indLeft < leftElements && indRight < elements){
		void* leftCurrent = (char*)arrayCopy + indLeft * element_size;
		void* rightCurrent = (char*)arrayCopy + indRight * element_size;
		if (comparator(leftCurrent, rightCurrent) < 0){
			memcpy((char*)result + indResult * element_size, leftCurrent, element_size);
			indLeft++;
		} else{
			memcpy((char*)result + indResult * element_size, rightCurrent, element_size);
			indRight++;
		}
		indResult++;
	}
	while (indLeft < leftElements){
		void* leftCurrent = (char*)arrayCopy + indLeft * element_size;
		memcpy((char*)result + indResult * element_size, leftCurrent, element_size);
		indLeft++;
		indResult++;
	}
	while (indRight < elements){
		void* rightCurrent = (char*)arrayCopy + indRight * element_size;
		memcpy((char*)result + indResult * element_size, rightCurrent, element_size);
		indRight++;
		indResult++;
	}
	memcpy(arrayCopy, result, elements * element_size);
	free(result);
	return 0;
}