#include "str.h"
#include<stddef.h>

char *my_strcpy(char *dest, char *src){
	char *it_dest = dest;
	char *it_src = src;
	for (; *it_src != '\0'; it_src++, it_dest++)
		*it_dest = *it_src;
	return dest;
}

char *my_strcat(char *dest, char *src){
	char *it_dest = dest;
	while (*it_dest != '\0')
		it_dest++;
	it_dest = my_strcpy(it_dest, src);
	return dest;
}

int my_strcmp(char *lhs, char *rhs){
	char *it_lhs = lhs;
	char *it_rhs = rhs;
	for (; *it_lhs != '\0' && *it_rhs != '\0'; it_lhs++, it_rhs++)
		if (*it_lhs - *it_rhs != 0)
			break;
	return *it_lhs - *it_rhs;
}

size_t my_strlen(char *str){
	size_t len = 0;
	char *it_str = (char*)str;
	while (*it_str != '\0'){
		it_str++;
		len++;
	}
	return len;
}