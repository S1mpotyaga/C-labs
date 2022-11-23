#include "str.h"
#include <stddef.h>

char* my_strcpy(char* restrict s_dest, const char* restrict s_from) {
	char* restrict it_dest = s_dest;
	char* restrict it_from = (char*) s_from;
	while ((*it_from) != '\0') {
		*it_dest = (*it_from);
		it_dest++;
		it_from++;
	}
	*it_dest = '\0';
	return s_dest;
}

char *my_strcat(char* restrict dest, const char* restrict from) {
	char* restrict it_dest = dest;
	while ((*it_dest) != '\0') it_dest++;
	my_strcpy(it_dest, from);
	return dest;
}

int my_strcmp(const char* s, const char* t) {
	char* it_s = (char*) s;
	char* it_t = (char*) t;
	while ((*it_s) != '\0' && (*it_t) != '\0') {
		if ((*it_s) != (*it_t)) return (*it_s) - (*it_t);
		it_s++;
		it_t++;
	}
	return (*it_s) - (*it_t);
}

size_t my_strlen(const char* s) {
	size_t len = 0;
	char* it_s = (char*) s;
	while ((*it_s) != '\0') {
		len++;
		it_s++;
	}
	return len;
}