#include<stddef.h>

#ifndef _MERGESORT_

#define _MERGESORT_

int mergesort(
	void* array,
	size_t elements, size_t element_size,
	int (*comparator)(const void *, const void *)
);

#endif