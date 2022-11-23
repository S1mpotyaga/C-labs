#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static void copy(void* startFrom, void* startRes, size_t size) {
    char* itFrom = (char*) startFrom;
    char* itRes = (char*) startRes;
    for (size_t i = 0; i < size; i++) {
        *itRes = *(itFrom);
        itFrom++;
        itRes++;
    }
}

int mergesort(

    void *array,
    size_t elements, size_t element_size,
    int (*comparator)(const void *, const void *)
) {
    if (elements <= 1) return 0;
    size_t l = elements / 2;
    size_t r = elements - l;
    if (mergesort(array, l, element_size, comparator) != 0)
        return -1;
    if (mergesort(array + l * element_size, r, element_size, comparator) != 0)
        return -1;

    void* result = malloc(elements * element_size);
    
    if (result == NULL) return -1;
    void* itLeft = array;
    void* itRight = array + l * element_size;

    void* leftEnd = array + l * element_size;
    void* rightEnd = array + elements * element_size;
    
    size_t resultSize = 0;
    while (itLeft != leftEnd && itRight != rightEnd) {
        if (comparator((const void*) itLeft, (const void*) itRight) <= 0) {
            copy(itLeft, result + resultSize * element_size, element_size);
            itLeft += element_size;
        } else {
            copy(itRight, result + resultSize * element_size, element_size);
            itRight += element_size;
        }
        resultSize++;
    }

    while (itLeft != leftEnd) {
        copy(itLeft, result + resultSize * element_size, element_size);
        itLeft += element_size;
        resultSize++;
    }

    while (itRight != rightEnd) {
        copy(itRight, result + resultSize * element_size, element_size);
        itRight += element_size;
        resultSize++;
    }

    copy(result, array, elements * element_size);
    free(result);
    return 0;
}
