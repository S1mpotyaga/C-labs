#include "str.h"
#include <stddef.h>

char *my_strcpy(char *dest, const char *src){
	char *it_dest = (char *)dest;
	const char *it_src = src;
	for (; *it_src != '\0'; it_src++, it_dest++){
		*it_dest = *it_src;
	}
	return dest;
}

char *my_strcat(char *dest, const char *src){
	char *it_dest = dest;
	while (*it_dest != '\0'){
		it_dest++;
	}
	it_dest = my_strcpy(it_dest, src);
	return dest;
}

int my_strcmp(const char *it_lhs, const char *it_rhs){
	for (; *it_lhs != '\0' && *it_rhs != '\0'; it_lhs++, it_rhs++){
		if (*it_lhs != *it_rhs){
			break;
		}
	}
	return *it_lhs - *it_rhs;
}

size_t my_strlen(const char *it_str){
	size_t len = 0;
	while (*it_str != '\0'){
		it_str++;
		len++;
	}
	return len;
}