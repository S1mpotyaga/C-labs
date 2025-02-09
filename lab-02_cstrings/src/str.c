#include "str.h"

char *strcpy(char *dest, char *src){
	char *it_dest = dest;
	char *it_src = src;
	for (; *it_src != '\0'; it_src++, it_dest++)
		*it_dest = *it_src;
	return dest;
}

char *strcat(char *dest, char *src){
	char *it_dest = dest;
	while (*it_dest != '\0')
		it_dest++;
	it_dest = strcpy(it_dest, src);
	return dest;
}

int strcmp(char *lhs, char *rhs){
	char *it_lhs = lhs;
	char *it_rhs = rhs;
	for (; *it_lhs != '\0' && *it_rhs != '\0'; it_lhs++, it_rhs++){
		int tmp = *it_lhs - *it_rhs;
		if (tmp < 0)
			return tmp;
		else if (tmp > 0)
			return tmp;
	}
	return 0;
}

size_t strlen(char *str){
	char *it_str = str;
	while (*it_str != '\0')
		it_str++;
	return (size_t)(it_str - str);
}