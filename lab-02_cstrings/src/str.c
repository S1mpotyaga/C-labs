#include "str.h"
#include <stddef.h>

char* my_strcpy(char* s_dest, char* s_from) {
	char* it_dest = s_dest;
	char* it_from = s_from;
	while ((*it_from) != '\0') {
		*it_dest = (*it_from);
		it_dest++;
		it_from++;
	}
	*it_dest = '\0';
	return s_dest;
}

char *my_strcat(char* dest, char* from) {
	char* it_dest = dest;
	while ((*it_dest) != '\0') it_dest++;
	my_strcpy(it_dest, from);
	return dest;
}

int my_strcmp(char* s, char* t) {
	while ((*s) != '\0' && (*t) != '\0') {
		if ((*s) != (*t)) return (*s) - (*t);
		s++;
		t++;
	}
	return (*s) - (*t);
}

size_t my_strlen(char* s) {
	size_t len = 0;
	while ((*s) != '\0') {
		len++;
		s++;
	}
	return len;
}